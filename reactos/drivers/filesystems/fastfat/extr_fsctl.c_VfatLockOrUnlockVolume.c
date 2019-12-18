#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_12__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_23__ {struct TYPE_23__* Flink; } ;
struct TYPE_25__ {int OpenHandleCount; int /*<<< orphan*/  Flags; TYPE_12__* VolumeFcb; TYPE_6__ FcbListHead; TYPE_1__* FATFileObject; } ;
struct TYPE_24__ {TYPE_5__* FsContext; } ;
struct TYPE_22__ {int OpenHandleCount; int /*<<< orphan*/  PathNameU; int /*<<< orphan*/  RefCount; int /*<<< orphan*/ * FileObject; int /*<<< orphan*/  Flags; } ;
struct TYPE_21__ {TYPE_2__* Stack; TYPE_7__* FileObject; TYPE_8__* DeviceExt; } ;
struct TYPE_20__ {int /*<<< orphan*/  Flags; } ;
struct TYPE_19__ {int /*<<< orphan*/  FileObject; } ;
struct TYPE_18__ {TYPE_3__* Vpb; } ;
struct TYPE_17__ {int /*<<< orphan*/  Flags; } ;
typedef  TYPE_3__* PVPB ;
typedef  TYPE_4__* PVFAT_IRP_CONTEXT ;
typedef  TYPE_5__* PVFATFCB ;
typedef  TYPE_6__* PLIST_ENTRY ;
typedef  TYPE_7__* PFILE_OBJECT ;
typedef  TYPE_8__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ BooleanFlagOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* CONTAINING_RECORD (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClearFlag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FCB_IS_VOLUME ; 
 int /*<<< orphan*/  FSRTL_VOLUME_LOCK ; 
 int /*<<< orphan*/  FSRTL_VOLUME_LOCK_FAILED ; 
 int /*<<< orphan*/  FSRTL_VOLUME_UNLOCK ; 
 int /*<<< orphan*/  FcbListEntry ; 
 int /*<<< orphan*/  FsRtlNotifyVolumeEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_ACCESS_DENIED ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  SetDirtyStatus (TYPE_8__*,scalar_t__) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VCB_CLEAR_DIRTY ; 
 int /*<<< orphan*/  VCB_IS_DIRTY ; 
 int /*<<< orphan*/  VCB_IS_SYS_OR_HAS_PAGE ; 
 int /*<<< orphan*/  VCB_VOLUME_LOCKED ; 
 int /*<<< orphan*/  VFATFCB ; 
 int /*<<< orphan*/  VPB_LOCKED ; 
 int /*<<< orphan*/  VfatFlushVolume (TYPE_8__*,TYPE_12__*) ; 
 int /*<<< orphan*/  vfatFCBIsDirectory (TYPE_5__*) ; 

__attribute__((used)) static
NTSTATUS
VfatLockOrUnlockVolume(
    PVFAT_IRP_CONTEXT IrpContext,
    BOOLEAN Lock)
{
    PFILE_OBJECT FileObject;
    PDEVICE_EXTENSION DeviceExt;
    PVFATFCB Fcb;
    PVPB Vpb;

    DPRINT("VfatLockOrUnlockVolume(%p, %d)\n", IrpContext, Lock);

    DeviceExt = IrpContext->DeviceExt;
    FileObject = IrpContext->FileObject;
    Fcb = FileObject->FsContext;
    Vpb = DeviceExt->FATFileObject->Vpb;

    /* Only allow locking with the volume open */
    if (!BooleanFlagOn(Fcb->Flags, FCB_IS_VOLUME))
    {
        return STATUS_ACCESS_DENIED;
    }

    /* Bail out if it's already in the demanded state */
    if ((BooleanFlagOn(DeviceExt->Flags, VCB_VOLUME_LOCKED) && Lock) ||
        (!BooleanFlagOn(DeviceExt->Flags, VCB_VOLUME_LOCKED) && !Lock))
    {
        return STATUS_ACCESS_DENIED;
    }

    /* Bail out if it's already in the demanded state */
    if ((BooleanFlagOn(Vpb->Flags, VPB_LOCKED) && Lock) ||
        (!BooleanFlagOn(Vpb->Flags, VPB_LOCKED) && !Lock))
    {
        return STATUS_ACCESS_DENIED;
    }

    if (Lock)
    {
        FsRtlNotifyVolumeEvent(IrpContext->Stack->FileObject, FSRTL_VOLUME_LOCK);
    }

    /* Deny locking if we're not alone */
    if (Lock && DeviceExt->OpenHandleCount != 1)
    {
        PLIST_ENTRY ListEntry;

#if 1
        /* FIXME: Hack that allows locking the system volume on
         * boot so that autochk can run properly
         * That hack is, on purpose, really restrictive
         * it will only allow locking with two directories
         * open: current directory of smss and autochk.
         */
        BOOLEAN ForceLock = TRUE;
        ULONG HandleCount = 0;

        /* Only allow boot volume */
        if (BooleanFlagOn(DeviceExt->Flags, VCB_IS_SYS_OR_HAS_PAGE))
        {
            /* We'll browse all the FCB */
            ListEntry = DeviceExt->FcbListHead.Flink;
            while (ListEntry != &DeviceExt->FcbListHead)
            {
                Fcb = CONTAINING_RECORD(ListEntry, VFATFCB, FcbListEntry);
                ListEntry = ListEntry->Flink;

                /* If no handle: that FCB is no problem for locking
                 * so ignore it
                 */
                if (Fcb->OpenHandleCount == 0)
                {
                    continue;
                }

                /* Not a dir? We're no longer at boot */
                if (!vfatFCBIsDirectory(Fcb))
                {
                    ForceLock = FALSE;
                    break;
                }

                /* If we have cached initialized and several handles, we're
                   not in the boot case
                 */
                if (Fcb->FileObject != NULL && Fcb->OpenHandleCount > 1)
                {
                    ForceLock = FALSE;
                    break;
                }

                /* Count the handles */
                HandleCount += Fcb->OpenHandleCount;
                /* More than two handles? Then, we're not booting anymore */
                if (HandleCount > 2)
                {
                    ForceLock = FALSE;
                    break;
                }
            }
        }
        else
        {
            ForceLock = FALSE;
        }

        /* Here comes the hack, ignore the failure! */
        if (!ForceLock)
        {
#endif

        DPRINT1("Can't lock: %u opened\n", DeviceExt->OpenHandleCount);

        ListEntry = DeviceExt->FcbListHead.Flink;
        while (ListEntry != &DeviceExt->FcbListHead)
        {
            Fcb = CONTAINING_RECORD(ListEntry, VFATFCB, FcbListEntry);
            ListEntry = ListEntry->Flink;

            if (Fcb->OpenHandleCount  > 0)
            {
                DPRINT1("Opened (%u - %u): %wZ\n", Fcb->OpenHandleCount, Fcb->RefCount, &Fcb->PathNameU);
            }
        }

        FsRtlNotifyVolumeEvent(IrpContext->Stack->FileObject, FSRTL_VOLUME_LOCK_FAILED);

        return STATUS_ACCESS_DENIED;

#if 1
        /* End of the hack: be verbose about its usage,
         * just in case we would mess up everything!
         */
        }
        else
        {
            DPRINT1("HACK: Using lock-hack!\n");
        }
#endif
    }

    /* Finally, proceed */
    if (Lock)
    {
        /* Flush volume & files */
        VfatFlushVolume(DeviceExt, DeviceExt->VolumeFcb);

        /* The volume is now clean */
        if (BooleanFlagOn(DeviceExt->VolumeFcb->Flags, VCB_CLEAR_DIRTY) &&
            BooleanFlagOn(DeviceExt->VolumeFcb->Flags, VCB_IS_DIRTY))
        {
            /* Drop the dirty bit */
            if (NT_SUCCESS(SetDirtyStatus(DeviceExt, FALSE)))
                ClearFlag(DeviceExt->VolumeFcb->Flags, VCB_IS_DIRTY);
        }

        DeviceExt->Flags |= VCB_VOLUME_LOCKED;
        Vpb->Flags |= VPB_LOCKED;
    }
    else
    {
        DeviceExt->Flags &= ~VCB_VOLUME_LOCKED;
        Vpb->Flags &= ~VPB_LOCKED;

        FsRtlNotifyVolumeEvent(IrpContext->Stack->FileObject, FSRTL_VOLUME_UNLOCK);
    }

    return STATUS_SUCCESS;
}