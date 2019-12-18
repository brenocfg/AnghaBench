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
struct TYPE_6__ {scalar_t__ Status; } ;
struct TYPE_7__ {TYPE_1__ IoStatus; } ;
typedef  TYPE_2__* PIRP ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 int /*<<< orphan*/  IO_NETWORK_INCREMENT ; 
 int /*<<< orphan*/  IoAcquireCancelSpinLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IoCompleteRequest (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IoReleaseCancelSpinLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IoSetCancelRoutine (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ STATUS_PENDING ; 

NTSTATUS IRPFinish( PIRP Irp, NTSTATUS Status ) {
    KIRQL OldIrql;

    if (Status != STATUS_PENDING) {
        Irp->IoStatus.Status = Status;
        IoAcquireCancelSpinLock(&OldIrql);
        (void)IoSetCancelRoutine( Irp, NULL );
        IoReleaseCancelSpinLock(OldIrql);

        IoCompleteRequest( Irp, IO_NETWORK_INCREMENT );
    }

    return Status;
}