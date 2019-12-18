#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ Information; } ;
struct TYPE_12__ {TYPE_2__ IoStatus; } ;
struct TYPE_11__ {scalar_t__ DeviceObject; } ;
struct TYPE_10__ {scalar_t__ DeviceObject; TYPE_7__* Irp; TYPE_1__* DeviceExt; } ;
struct TYPE_8__ {int /*<<< orphan*/  DirResource; } ;
typedef  TYPE_3__* PVFAT_IRP_CONTEXT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,scalar_t__,TYPE_7__*) ; 
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VfatCleanupFile (TYPE_3__*) ; 
 TYPE_4__* VfatGlobalData ; 

NTSTATUS
VfatCleanup(
    PVFAT_IRP_CONTEXT IrpContext)
{
    BOOLEAN Deleted;

    DPRINT("VfatCleanup(DeviceObject %p, Irp %p)\n", IrpContext->DeviceObject, IrpContext->Irp);

    if (IrpContext->DeviceObject == VfatGlobalData->DeviceObject)
    {
        IrpContext->Irp->IoStatus.Information = 0;
        return STATUS_SUCCESS;
    }

    ExAcquireResourceExclusiveLite(&IrpContext->DeviceExt->DirResource, TRUE);
    Deleted = VfatCleanupFile(IrpContext);
    if (!Deleted) ExReleaseResourceLite(&IrpContext->DeviceExt->DirResource);

    IrpContext->Irp->IoStatus.Information = 0;
    return STATUS_SUCCESS;
}