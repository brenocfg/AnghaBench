#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int SocketType; int /*<<< orphan*/  TdiAddressObject; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PAFDFCB ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 scalar_t__ AfdEventDisconnect ; 
 scalar_t__ AfdEventError ; 
 scalar_t__ AfdEventReceive ; 
 scalar_t__ AfdEventReceiveDatagramHandler ; 
 scalar_t__ ClientEventChainedReceive ; 
 scalar_t__ ClientEventReceiveExpedited ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
#define  SOCK_DGRAM 130 
#define  SOCK_RAW 129 
#define  SOCK_STREAM 128 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TDI_EVENT_CHAINED_RECEIVE ; 
 int /*<<< orphan*/  TDI_EVENT_DISCONNECT ; 
 int /*<<< orphan*/  TDI_EVENT_ERROR ; 
 int /*<<< orphan*/  TDI_EVENT_RECEIVE ; 
 int /*<<< orphan*/  TDI_EVENT_RECEIVE_DATAGRAM ; 
 int /*<<< orphan*/  TDI_EVENT_RECEIVE_EXPEDITED ; 
 int /*<<< orphan*/  TdiSetEventHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

NTSTATUS AfdRegisterEventHandlers(
    PAFDFCB FCB)
{
    NTSTATUS Status;

    assert(FCB->TdiAddressObject);

    /* Report errors for all types of sockets */
    Status = TdiSetEventHandler(FCB->TdiAddressObject,
        TDI_EVENT_ERROR,
        (PVOID)AfdEventError,
        (PVOID)FCB);
    if (!NT_SUCCESS(Status)) { return Status; }

    switch (FCB->SocketType) {
    case SOCK_STREAM:
        Status = TdiSetEventHandler(FCB->TdiAddressObject,
            TDI_EVENT_DISCONNECT,
            (PVOID)AfdEventDisconnect,
            (PVOID)FCB);
        if (!NT_SUCCESS(Status)) { return Status; }

        Status = TdiSetEventHandler(FCB->TdiAddressObject,
            TDI_EVENT_RECEIVE,
            (PVOID)AfdEventReceive,
            (PVOID)FCB);
        if (!NT_SUCCESS(Status)) { return Status; }

        Status = TdiSetEventHandler(FCB->TdiAddressObject,
            TDI_EVENT_RECEIVE_EXPEDITED,
            (PVOID)ClientEventReceiveExpedited,
            (PVOID)FCB);
        if (!NT_SUCCESS(Status)) { return Status; }

        Status = TdiSetEventHandler(FCB->TdiAddressObject,
            TDI_EVENT_CHAINED_RECEIVE,
            (PVOID)ClientEventChainedReceive,
            (PVOID)FCB);
        if (!NT_SUCCESS(Status)) { return Status; }
        break;

    case SOCK_DGRAM:
    case SOCK_RAW:
        Status = TdiSetEventHandler(FCB->TdiAddressObject,
            TDI_EVENT_RECEIVE_DATAGRAM,
            (PVOID)AfdEventReceiveDatagramHandler,
            (PVOID)FCB);
        if (!NT_SUCCESS(Status)) { return Status; }
    }
    return STATUS_SUCCESS;
}