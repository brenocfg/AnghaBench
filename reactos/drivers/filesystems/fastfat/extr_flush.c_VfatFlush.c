#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  DirResource; } ;
struct TYPE_18__ {scalar_t__ DeviceObject; } ;
struct TYPE_17__ {int /*<<< orphan*/  MainResource; int /*<<< orphan*/  Flags; } ;
struct TYPE_16__ {scalar_t__ DeviceObject; TYPE_3__* Irp; TYPE_7__* DeviceExt; TYPE_1__* FileObject; } ;
struct TYPE_14__ {scalar_t__ Information; } ;
struct TYPE_15__ {TYPE_2__ IoStatus; } ;
struct TYPE_13__ {scalar_t__ FsContext; } ;
typedef  TYPE_4__* PVFAT_IRP_CONTEXT ;
typedef  TYPE_5__* PVFATFCB ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_5__*) ; 
 scalar_t__ BooleanFlagOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FCB_IS_VOLUME ; 
 int /*<<< orphan*/  STATUS_INVALID_DEVICE_REQUEST ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VfatFlushFile (TYPE_7__*,TYPE_5__*) ; 
 int /*<<< orphan*/  VfatFlushVolume (TYPE_7__*,TYPE_5__*) ; 
 TYPE_6__* VfatGlobalData ; 

NTSTATUS
VfatFlush(
    PVFAT_IRP_CONTEXT IrpContext)
{
    NTSTATUS Status;
    PVFATFCB Fcb;

    /* This request is not allowed on the main device object. */
    if (IrpContext->DeviceObject == VfatGlobalData->DeviceObject)
    {
        IrpContext->Irp->IoStatus.Information = 0;
        return STATUS_INVALID_DEVICE_REQUEST;
    }

    Fcb = (PVFATFCB)IrpContext->FileObject->FsContext;
    ASSERT(Fcb);

    if (BooleanFlagOn(Fcb->Flags, FCB_IS_VOLUME))
    {
        ExAcquireResourceExclusiveLite(&IrpContext->DeviceExt->DirResource, TRUE);
        Status = VfatFlushVolume(IrpContext->DeviceExt, Fcb);
        ExReleaseResourceLite(&IrpContext->DeviceExt->DirResource);
    }
    else
    {
        ExAcquireResourceExclusiveLite(&Fcb->MainResource, TRUE);
        Status = VfatFlushFile(IrpContext->DeviceExt, Fcb);
        ExReleaseResourceLite (&Fcb->MainResource);
    }

    IrpContext->Irp->IoStatus.Information = 0;
    return Status;
}