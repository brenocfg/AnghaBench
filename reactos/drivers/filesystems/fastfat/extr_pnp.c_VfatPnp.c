#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  StorageDevice; } ;
struct TYPE_9__ {int /*<<< orphan*/  Irp; int /*<<< orphan*/  Flags; TYPE_2__* Stack; } ;
struct TYPE_8__ {int MinorFunction; TYPE_1__* DeviceObject; } ;
struct TYPE_7__ {int /*<<< orphan*/  DeviceExtension; } ;
typedef  TYPE_3__* PVFAT_IRP_CONTEXT ;
typedef  TYPE_4__* PVCB ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_3__*) ; 
 int /*<<< orphan*/  IRPCONTEXT_COMPLETE ; 
#define  IRP_MN_CANCEL_REMOVE_DEVICE 131 
#define  IRP_MN_QUERY_REMOVE_DEVICE 130 
#define  IRP_MN_REMOVE_DEVICE 129 
#define  IRP_MN_SURPRISE_REMOVAL 128 
 int /*<<< orphan*/  IoCallDriver (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IoSkipCurrentIrpStackLocation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_NOT_IMPLEMENTED ; 

NTSTATUS
VfatPnp(
    PVFAT_IRP_CONTEXT IrpContext)
{
    PVCB Vcb = NULL;
    NTSTATUS Status;

    /* PRECONDITION */
    ASSERT(IrpContext);

    switch (IrpContext->Stack->MinorFunction)
    {
        case IRP_MN_QUERY_REMOVE_DEVICE:
        case IRP_MN_SURPRISE_REMOVAL:
        case IRP_MN_REMOVE_DEVICE:
        case IRP_MN_CANCEL_REMOVE_DEVICE:
            Status = STATUS_NOT_IMPLEMENTED;
            break;

        default:
            IoSkipCurrentIrpStackLocation(IrpContext->Irp);
            Vcb = (PVCB)IrpContext->Stack->DeviceObject->DeviceExtension;
            IrpContext->Flags &= ~IRPCONTEXT_COMPLETE;
            Status = IoCallDriver(Vcb->StorageDevice, IrpContext->Irp);
    }

    return Status;
}