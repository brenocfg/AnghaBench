#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* Vpb; int /*<<< orphan*/  page_file_count; } ;
typedef  TYPE_4__ device_extension ;
struct TYPE_14__ {TYPE_4__* DeviceExtension; } ;
struct TYPE_10__ {int Type; scalar_t__ InPath; } ;
struct TYPE_11__ {TYPE_2__ UsageNotification; } ;
struct TYPE_13__ {TYPE_3__ Parameters; } ;
struct TYPE_9__ {int /*<<< orphan*/  RealDevice; } ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  TYPE_5__* PIO_STACK_LOCATION ;
typedef  TYPE_6__* PDEVICE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
#define  DeviceUsageTypeDumpFile 130 
#define  DeviceUsageTypeHibernation 129 
#define  DeviceUsageTypePaging 128 
 int /*<<< orphan*/  IoAdjustPagingPathCount (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  IoCallDriver (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* IoGetCurrentIrpStackLocation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IoSkipCurrentIrpStackLocation (int /*<<< orphan*/ ) ; 

__attribute__((used)) static NTSTATUS pnp_device_usage_notification(PDEVICE_OBJECT DeviceObject, PIRP Irp) {
    PIO_STACK_LOCATION IrpSp = IoGetCurrentIrpStackLocation(Irp);
    device_extension* Vcb = DeviceObject->DeviceExtension;

    if (IrpSp->Parameters.UsageNotification.InPath) {
        switch (IrpSp->Parameters.UsageNotification.Type) {
            case DeviceUsageTypePaging:
            case DeviceUsageTypeHibernation:
            case DeviceUsageTypeDumpFile:
                IoAdjustPagingPathCount(&Vcb->page_file_count, IrpSp->Parameters.UsageNotification.InPath);
                break;

            default:
                break;
        }
    }

    IoSkipCurrentIrpStackLocation(Irp);
    return IoCallDriver(Vcb->Vpb->RealDevice, Irp);
}