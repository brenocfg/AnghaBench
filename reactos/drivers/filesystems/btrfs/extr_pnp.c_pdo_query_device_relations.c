#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_16__ {int Count; int /*<<< orphan*/ * Objects; } ;
struct TYPE_11__ {scalar_t__ Type; } ;
struct TYPE_12__ {TYPE_1__ QueryDeviceRelations; } ;
struct TYPE_15__ {TYPE_2__ Parameters; } ;
struct TYPE_13__ {scalar_t__ Information; int /*<<< orphan*/  Status; } ;
struct TYPE_14__ {TYPE_3__ IoStatus; } ;
typedef  TYPE_4__* PIRP ;
typedef  TYPE_5__* PIO_STACK_LOCATION ;
typedef  TYPE_6__* PDEVICE_RELATIONS ;
typedef  int /*<<< orphan*/  PDEVICE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  DEVICE_RELATIONS ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 int /*<<< orphan*/  ERR (char*) ; 
 TYPE_6__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_5__* IoGetCurrentIrpStackLocation (TYPE_4__*) ; 
 int /*<<< orphan*/  ObReferenceObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PagedPool ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ TargetDeviceRelation ; 

__attribute__((used)) static NTSTATUS pdo_query_device_relations(PDEVICE_OBJECT pdo, PIRP Irp) {
    PIO_STACK_LOCATION IrpSp = IoGetCurrentIrpStackLocation(Irp);
    PDEVICE_RELATIONS device_relations;

    if (IrpSp->Parameters.QueryDeviceRelations.Type != TargetDeviceRelation)
        return Irp->IoStatus.Status;

    device_relations = ExAllocatePoolWithTag(PagedPool, sizeof(DEVICE_RELATIONS), ALLOC_TAG);
    if (!device_relations) {
        ERR("out of memory\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    device_relations->Count = 1;
    device_relations->Objects[0] = pdo;

    ObReferenceObject(pdo);

    Irp->IoStatus.Information = (ULONG_PTR)device_relations;

    return STATUS_SUCCESS;
}