#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ USHORT ;
struct TYPE_8__ {scalar_t__ Port; scalar_t__ Protocol; scalar_t__ Sharers; } ;
struct TYPE_7__ {struct TYPE_7__* Flink; } ;
typedef  TYPE_1__* PLIST_ENTRY ;
typedef  int /*<<< orphan*/  PIP_ADDRESS ;
typedef  TYPE_2__* PADDRESS_FILE ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRESS_FILE ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_1__ AddressFileListHead ; 
 int /*<<< orphan*/  AddressFileListLock ; 
 TYPE_2__* CONTAINING_RECORD (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InterlockedIncrement (scalar_t__*) ; 
 int /*<<< orphan*/  ListEntry ; 
 int /*<<< orphan*/  TcpipAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TcpipReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

PADDRESS_FILE AddrFindShared(
    PIP_ADDRESS BindAddress,
    USHORT Port,
    USHORT Protocol)
{
    PLIST_ENTRY CurrentEntry;
    KIRQL OldIrql;
    PADDRESS_FILE Current = NULL;

    TcpipAcquireSpinLock(&AddressFileListLock, &OldIrql);

    CurrentEntry = AddressFileListHead.Flink;
    while (CurrentEntry != &AddressFileListHead) {
        Current = CONTAINING_RECORD(CurrentEntry, ADDRESS_FILE, ListEntry);

        /* See if this address matches the search criteria */
        if ((Current->Port == Port) &&
            (Current->Protocol == Protocol))
        {
            /* Increase the sharer count */
            ASSERT(Current->Sharers != 0);
            InterlockedIncrement(&Current->Sharers);
            break;
        }

        CurrentEntry = CurrentEntry->Flink;
        Current = NULL;
    }

    TcpipReleaseSpinLock(&AddressFileListLock, OldIrql);

    return Current;
}