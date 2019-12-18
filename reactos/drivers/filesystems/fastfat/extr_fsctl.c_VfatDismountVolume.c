#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  FatResource; int /*<<< orphan*/  Flags; TYPE_5__* VolumeFcb; TYPE_5__* RootFcb; int /*<<< orphan*/  FcbListHead; } ;
struct TYPE_20__ {scalar_t__ FsContext; } ;
struct TYPE_19__ {int /*<<< orphan*/  Flags; } ;
struct TYPE_18__ {TYPE_3__* DeviceObject; TYPE_1__* Stack; TYPE_6__* FileObject; TYPE_7__* DeviceExt; } ;
struct TYPE_17__ {TYPE_2__* Vpb; } ;
struct TYPE_16__ {int /*<<< orphan*/  Flags; } ;
struct TYPE_15__ {int /*<<< orphan*/  FileObject; } ;
typedef  TYPE_4__* PVFAT_IRP_CONTEXT ;
typedef  TYPE_5__* PVFATFCB ;
typedef  int /*<<< orphan*/  PLIST_ENTRY ;
typedef  TYPE_6__* PFILE_OBJECT ;
typedef  TYPE_7__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 scalar_t__ BooleanFlagOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* CONTAINING_RECORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClearFlag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,TYPE_4__*) ; 
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FSRTL_VOLUME_DISMOUNT ; 
 int /*<<< orphan*/  FcbListEntry ; 
 int /*<<< orphan*/  FsRtlNotifyVolumeEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsListEmpty (int /*<<< orphan*/ *) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveTailList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_ACCESS_DENIED ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_VOLUME_DISMOUNTED ; 
 int /*<<< orphan*/  SetDirtyStatus (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VCB_CLEAR_DIRTY ; 
 int /*<<< orphan*/  VCB_DISMOUNT_PENDING ; 
 int /*<<< orphan*/  VCB_GOOD ; 
 int /*<<< orphan*/  VCB_IS_DIRTY ; 
 int /*<<< orphan*/  VCB_IS_SYS_OR_HAS_PAGE ; 
 int /*<<< orphan*/  VCB_VOLUME_LOCKED ; 
 int /*<<< orphan*/  VFATFCB ; 
 int /*<<< orphan*/  VPB_MOUNTED ; 
 int /*<<< orphan*/  VfatFlushVolume (TYPE_7__*,TYPE_5__*) ; 
 int /*<<< orphan*/  vfatDestroyFCB (TYPE_5__*) ; 

__attribute__((used)) static
NTSTATUS
VfatDismountVolume(
    PVFAT_IRP_CONTEXT IrpContext)
{
    PDEVICE_EXTENSION DeviceExt;
    PLIST_ENTRY NextEntry;
    PVFATFCB Fcb;
    PFILE_OBJECT FileObject;

    DPRINT("VfatDismountVolume(%p)\n", IrpContext);

    DeviceExt = IrpContext->DeviceExt;
    FileObject = IrpContext->FileObject;

    /* We HAVE to be locked. Windows also allows dismount with no lock
     * but we're here mainly for 1st stage, so KISS
     */
    if (!BooleanFlagOn(DeviceExt->Flags, VCB_VOLUME_LOCKED))
    {
        return STATUS_ACCESS_DENIED;
    }

    /* Deny dismount of boot volume */
    if (BooleanFlagOn(DeviceExt->Flags, VCB_IS_SYS_OR_HAS_PAGE))
    {
        return STATUS_ACCESS_DENIED;
    }

    /* Race condition? */
    if (BooleanFlagOn(DeviceExt->Flags, VCB_DISMOUNT_PENDING))
    {
        return STATUS_VOLUME_DISMOUNTED;
    }

    /* Notify we'll dismount. Pass that point there's no reason we fail */
    FsRtlNotifyVolumeEvent(IrpContext->Stack->FileObject, FSRTL_VOLUME_DISMOUNT);

    ExAcquireResourceExclusiveLite(&DeviceExt->FatResource, TRUE);

    /* Flush volume & files */
    VfatFlushVolume(DeviceExt, (PVFATFCB)FileObject->FsContext);

    /* The volume is now clean */
    if (BooleanFlagOn(DeviceExt->VolumeFcb->Flags, VCB_CLEAR_DIRTY) &&
        BooleanFlagOn(DeviceExt->VolumeFcb->Flags, VCB_IS_DIRTY))
    {
        /* Drop the dirty bit */
        if (NT_SUCCESS(SetDirtyStatus(DeviceExt, FALSE)))
            DeviceExt->VolumeFcb->Flags &= ~VCB_IS_DIRTY;
    }

    /* Rebrowse the FCB in order to free them now */
    while (!IsListEmpty(&DeviceExt->FcbListHead))
    {
        NextEntry = RemoveTailList(&DeviceExt->FcbListHead);
        Fcb = CONTAINING_RECORD(NextEntry, VFATFCB, FcbListEntry);

        if (Fcb == DeviceExt->RootFcb)
            DeviceExt->RootFcb = NULL;
        else if (Fcb == DeviceExt->VolumeFcb)
            DeviceExt->VolumeFcb = NULL;

        vfatDestroyFCB(Fcb);
    }

    /* We are uninitializing, the VCB cannot be used anymore */
    ClearFlag(DeviceExt->Flags, VCB_GOOD);

    /* Mark we're being dismounted */
    DeviceExt->Flags |= VCB_DISMOUNT_PENDING;
#ifndef ENABLE_SWAPOUT
    IrpContext->DeviceObject->Vpb->Flags &= ~VPB_MOUNTED;
#endif

    ExReleaseResourceLite(&DeviceExt->FatResource);

    return STATUS_SUCCESS;
}