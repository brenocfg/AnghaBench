#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ Port; scalar_t__ Protocol; int /*<<< orphan*/  Address; } ;
struct TYPE_12__ {scalar_t__ Port; scalar_t__ Protocol; TYPE_1__* Next; int /*<<< orphan*/ * Address; } ;
struct TYPE_11__ {struct TYPE_11__* Flink; } ;
typedef  TYPE_1__* PLIST_ENTRY ;
typedef  int /*<<< orphan*/ * PIP_ADDRESS ;
typedef  TYPE_2__* PAF_SEARCH ;
typedef  TYPE_3__* PADDRESS_FILE ;
typedef  int /*<<< orphan*/  KIRQL ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  A2S (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ADDRESS_FILE ; 
 scalar_t__ AddrReceiveMatch (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ AddressFileListHead ; 
 int /*<<< orphan*/  AddressFileListLock ; 
 TYPE_3__* CONTAINING_RECORD (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG_ADDRFILE ; 
 int /*<<< orphan*/  DereferenceObject (TYPE_3__*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  ListEntry ; 
 int /*<<< orphan*/  ReferenceObject (TYPE_3__*) ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  TcpipAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TcpipReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WN2H (scalar_t__) ; 

PADDRESS_FILE AddrSearchNext(
    PAF_SEARCH SearchContext)
{
    PLIST_ENTRY CurrentEntry;
    PIP_ADDRESS IPAddress;
    KIRQL OldIrql;
    PADDRESS_FILE Current = NULL;
    BOOLEAN Found = FALSE;
    PADDRESS_FILE StartingAddrFile;
    
    TcpipAcquireSpinLock(&AddressFileListLock, &OldIrql);

    if (SearchContext->Next == &AddressFileListHead)
    {
        TcpipReleaseSpinLock(&AddressFileListLock, OldIrql);
        return NULL;
    }

    /* Save this pointer so we can dereference it later */
    StartingAddrFile = CONTAINING_RECORD(SearchContext->Next, ADDRESS_FILE, ListEntry);

    CurrentEntry = SearchContext->Next;

    while (CurrentEntry != &AddressFileListHead) {
        Current = CONTAINING_RECORD(CurrentEntry, ADDRESS_FILE, ListEntry);

        IPAddress = &Current->Address;

        TI_DbgPrint(DEBUG_ADDRFILE, ("Comparing: ((%d, %d, %s), (%d, %d, %s)).\n",
            WN2H(Current->Port),
            Current->Protocol,
            A2S(IPAddress),
            WN2H(SearchContext->Port),
            SearchContext->Protocol,
            A2S(SearchContext->Address)));

        /* See if this address matches the search criteria */
        if ((Current->Port    == SearchContext->Port) &&
            (Current->Protocol == SearchContext->Protocol) &&
            (AddrReceiveMatch(IPAddress, SearchContext->Address))) {
            /* We've found a match */
            Found = TRUE;
            break;
        }
        CurrentEntry = CurrentEntry->Flink;
    }

    if (Found)
    {
        SearchContext->Next = CurrentEntry->Flink;

        if (SearchContext->Next != &AddressFileListHead)
        {
            /* Reference the next address file to prevent the link from disappearing behind our back */
            ReferenceObject(CONTAINING_RECORD(SearchContext->Next, ADDRESS_FILE, ListEntry));
        }

        /* Reference the returned address file before dereferencing the starting
         * address file because it may be that Current == StartingAddrFile */
        ReferenceObject(Current);
    }
    else
        Current = NULL;

    DereferenceObject(StartingAddrFile);

    TcpipReleaseSpinLock(&AddressFileListLock, OldIrql);

    return Current;
}