#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdo_device_extension ;
struct TYPE_16__ {int /*<<< orphan*/ * DeviceExtension; } ;
struct TYPE_15__ {int MinorFunction; } ;
struct TYPE_13__ {int /*<<< orphan*/  Status; } ;
struct TYPE_14__ {TYPE_1__ IoStatus; } ;
typedef  TYPE_2__* PIRP ;
typedef  TYPE_3__* PIO_STACK_LOCATION ;
typedef  TYPE_4__* PDEVICE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
#define  IRP_MN_CANCEL_REMOVE_DEVICE 135 
#define  IRP_MN_DEVICE_USAGE_NOTIFICATION 134 
#define  IRP_MN_QUERY_DEVICE_RELATIONS 133 
#define  IRP_MN_QUERY_ID 132 
#define  IRP_MN_QUERY_REMOVE_DEVICE 131 
#define  IRP_MN_REMOVE_DEVICE 130 
#define  IRP_MN_START_DEVICE 129 
#define  IRP_MN_SURPRISE_REMOVAL 128 
 TYPE_3__* IoGetCurrentIrpStackLocation (TYPE_2__*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 
 int /*<<< orphan*/  pdo_device_usage_notification (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  pdo_query_device_relations (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  pdo_query_id (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static NTSTATUS pdo_pnp(PDEVICE_OBJECT pdo, PIRP Irp) {
    PIO_STACK_LOCATION IrpSp = IoGetCurrentIrpStackLocation(Irp);
    pdo_device_extension* pdode = pdo->DeviceExtension;

    switch (IrpSp->MinorFunction) {
        case IRP_MN_QUERY_ID:
            return pdo_query_id(pdode, Irp);

        case IRP_MN_START_DEVICE:
        case IRP_MN_CANCEL_REMOVE_DEVICE:
        case IRP_MN_SURPRISE_REMOVAL:
        case IRP_MN_REMOVE_DEVICE:
            return STATUS_SUCCESS;

        case IRP_MN_QUERY_REMOVE_DEVICE:
            return STATUS_UNSUCCESSFUL;

        case IRP_MN_DEVICE_USAGE_NOTIFICATION:
            return pdo_device_usage_notification(pdode, Irp);

        case IRP_MN_QUERY_DEVICE_RELATIONS:
            return pdo_query_device_relations(pdo, Irp);
    }

    return Irp->IoStatus.Status;
}