#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  StorageDevice; } ;
struct TYPE_6__ {int /*<<< orphan*/  Flags; TYPE_1__* DeviceObject; int /*<<< orphan*/  Irp; } ;
struct TYPE_5__ {TYPE_3__* DeviceExtension; } ;
typedef  TYPE_2__* PNTFS_IRP_CONTEXT ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  TYPE_3__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  IRPCONTEXT_COMPLETE ; 
 int /*<<< orphan*/  IoCallDriver (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IoSkipCurrentIrpStackLocation (int /*<<< orphan*/ ) ; 

NTSTATUS
NtfsDeviceControl(PNTFS_IRP_CONTEXT IrpContext)
{
    PDEVICE_EXTENSION DeviceExt;
    PIRP Irp = IrpContext->Irp;

    DeviceExt = IrpContext->DeviceObject->DeviceExtension;
    IoSkipCurrentIrpStackLocation(Irp);

    /* Lower driver will complete - we don't have to */
    IrpContext->Flags &= ~IRPCONTEXT_COMPLETE;

    return IoCallDriver(DeviceExt->StorageDevice, Irp);
}