#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ Information; } ;
struct TYPE_12__ {TYPE_1__ IoStatus; } ;
struct TYPE_11__ {scalar_t__ DeviceObject; } ;
struct TYPE_10__ {scalar_t__ DeviceObject; void* PriorityBoost; TYPE_2__* DeviceExt; TYPE_5__* Irp; } ;
struct TYPE_9__ {int /*<<< orphan*/  DirResource; } ;
typedef  TYPE_3__* PVFAT_IRP_CONTEXT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_3__*) ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 scalar_t__ FILE_OPENED ; 
 void* IO_DISK_INCREMENT ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VfatCreateFile (scalar_t__,TYPE_5__*) ; 
 TYPE_4__* VfatGlobalData ; 

NTSTATUS
VfatCreate(
    PVFAT_IRP_CONTEXT IrpContext)
{
    NTSTATUS Status;

    ASSERT(IrpContext);

    if (IrpContext->DeviceObject == VfatGlobalData->DeviceObject)
    {
        /* DeviceObject represents FileSystem instead of logical volume */
        DPRINT ("FsdCreate called with file system\n");
        IrpContext->Irp->IoStatus.Information = FILE_OPENED;
        IrpContext->PriorityBoost = IO_DISK_INCREMENT;

        return STATUS_SUCCESS;
    }

    IrpContext->Irp->IoStatus.Information = 0;
    ExAcquireResourceExclusiveLite(&IrpContext->DeviceExt->DirResource, TRUE);
    Status = VfatCreateFile(IrpContext->DeviceObject, IrpContext->Irp);
    ExReleaseResourceLite(&IrpContext->DeviceExt->DirResource);

    if (NT_SUCCESS(Status))
        IrpContext->PriorityBoost = IO_DISK_INCREMENT;

    return Status;
}