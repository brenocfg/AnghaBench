#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* USHORT ;
struct TYPE_7__ {int /*<<< orphan*/  Flink; } ;
struct TYPE_6__ {int /*<<< orphan*/  Next; void* Protocol; void* Port; int /*<<< orphan*/  Address; } ;
typedef  int /*<<< orphan*/  PIP_ADDRESS ;
typedef  TYPE_1__* PAF_SEARCH ;
typedef  int /*<<< orphan*/  PADDRESS_FILE ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRESS_FILE ; 
 int /*<<< orphan*/  AddrSearchNext (TYPE_1__*) ; 
 TYPE_2__ AddressFileListHead ; 
 int /*<<< orphan*/  AddressFileListLock ; 
 int /*<<< orphan*/  CONTAINING_RECORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsListEmpty (TYPE_2__*) ; 
 int /*<<< orphan*/  ListEntry ; 
 int /*<<< orphan*/  ReferenceObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TcpipAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TcpipReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

PADDRESS_FILE AddrSearchFirst(
    PIP_ADDRESS Address,
    USHORT Port,
    USHORT Protocol,
    PAF_SEARCH SearchContext)
{
    KIRQL OldIrql;
    
    SearchContext->Address  = Address;
    SearchContext->Port     = Port;
    SearchContext->Protocol = Protocol;

    TcpipAcquireSpinLock(&AddressFileListLock, &OldIrql);

    SearchContext->Next = AddressFileListHead.Flink;

    if (!IsListEmpty(&AddressFileListHead))
        ReferenceObject(CONTAINING_RECORD(SearchContext->Next, ADDRESS_FILE, ListEntry));

    TcpipReleaseSpinLock(&AddressFileListLock, OldIrql);

    return AddrSearchNext(SearchContext);
}