﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WebSocketsSubsystem.generated.h"

class IWebSocket;

/**
 * 
 */
UCLASS()
class WEBSOCKETSHELPER_API UWebSocketsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category=WebSocketsHelper)
	bool Connect(const FString& Channel, const FString& ServerAddress);
	
	UFUNCTION(BlueprintCallable, Category=WebSocketsHelper)
	void Close(const FString& Channel);

	UFUNCTION(BlueprintCallable, Category=WebSocketsHelper)
	bool SendMessage(const FString& Channel, const FString& Message);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConnectionConnected, const FString&, Channel);
	UPROPERTY(BlueprintAssignable)
	FOnConnectionConnected OnConnectionConnected;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnConnectionClosed, const FString&, Channel, const FString&, Reason);
	UPROPERTY(BlueprintAssignable)
	FOnConnectionClosed OnConnectionClosed;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnConnectionError, const FString&, Channel, const FString&, Error);
	UPROPERTY(BlueprintAssignable)
	FOnConnectionError OnConnectionError;
	
private:
	void OnConnectionConnectedInternal(const FString& Channel);
	void OnConnectionErrorInternal(const FString& Channel, const FString& Error);
	void OnConnectionClosedInternal(const FString& Channel, const FString& Reason);
	
	TMap<FString, TSharedRef<IWebSocket>> WebSocketChannelMap;
};