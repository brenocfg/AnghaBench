#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_2__* FileObject; } ;
struct TYPE_11__ {int /*<<< orphan*/  Status; scalar_t__ Information; } ;
struct TYPE_14__ {TYPE_1__ IoStatus; int /*<<< orphan*/  Cancel; } ;
struct TYPE_13__ {int /*<<< orphan*/  CancelIrps; } ;
struct TYPE_12__ {scalar_t__ FsContext; } ;
typedef  TYPE_3__* PTRANSPORT_CONTEXT ;
typedef  TYPE_4__* PIRP ;
typedef  TYPE_5__* PIO_STACK_LOCATION ;
typedef  int /*<<< orphan*/  PDRIVER_CANCEL ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_IRP ; 
 int /*<<< orphan*/  IoAcquireCancelSpinLock (int /*<<< orphan*/ *) ; 
 TYPE_5__* IoGetCurrentIrpStackLocation (TYPE_4__*) ; 
 int /*<<< orphan*/  IoReleaseCancelSpinLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IoSetCancelRoutine (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_CANCELLED ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 

NTSTATUS DispPrepareIrpForCancel(
    PTRANSPORT_CONTEXT Context,
    PIRP Irp,
    PDRIVER_CANCEL CancelRoutine)
/*
 * FUNCTION: Prepare an IRP for cancellation
 * ARGUMENTS:
 *     Context       = Pointer to context information
 *     Irp           = Pointer to an I/O request packet
 *     CancelRoutine = Routine to be called when I/O request is cancelled
 * RETURNS:
 *     Status of operation
 */
{
    KIRQL OldIrql;
    PIO_STACK_LOCATION IrpSp;
    PTRANSPORT_CONTEXT TransContext;

    TI_DbgPrint(DEBUG_IRP, ("Called.\n"));

    IrpSp       = IoGetCurrentIrpStackLocation(Irp);
    TransContext = (PTRANSPORT_CONTEXT)IrpSp->FileObject->FsContext;

    IoAcquireCancelSpinLock(&OldIrql);

    if (!Irp->Cancel && !TransContext->CancelIrps) {
        (void)IoSetCancelRoutine(Irp, CancelRoutine);
        IoReleaseCancelSpinLock(OldIrql);

        TI_DbgPrint(DEBUG_IRP, ("Leaving (IRP at 0x%X can now be cancelled).\n", Irp));

        return STATUS_SUCCESS;
    }

    /* IRP has already been cancelled */

    IoReleaseCancelSpinLock(OldIrql);

    Irp->IoStatus.Status      = STATUS_CANCELLED;
    Irp->IoStatus.Information = 0;

    TI_DbgPrint(DEBUG_IRP, ("Leaving (IRP was already cancelled).\n"));

    return Irp->IoStatus.Status;
}