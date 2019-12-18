#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_24__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ ULONG ;
struct TYPE_28__ {int /*<<< orphan*/  FixedMedia; } ;
struct TYPE_33__ {int /*<<< orphan*/  StorageDevice; TYPE_2__ FatInfo; } ;
struct TYPE_32__ {TYPE_1__* RelatedFileObject; } ;
struct TYPE_29__ {int Length; int* Buffer; } ;
struct TYPE_31__ {scalar_t__ Flags; int /*<<< orphan*/  PathNameU; TYPE_4__* CloseContext; TYPE_3__ LongNameU; } ;
struct TYPE_30__ {int /*<<< orphan*/  CloseListEntry; } ;
struct TYPE_27__ {int /*<<< orphan*/  CloseContextLookasideList; int /*<<< orphan*/  CloseMutex; int /*<<< orphan*/  CloseCount; } ;
struct TYPE_26__ {TYPE_5__* FsContext; int /*<<< orphan*/  FileName; } ;
typedef  TYPE_4__* PVFAT_CLOSE_CONTEXT ;
typedef  TYPE_5__* PVFATFCB ;
typedef  int /*<<< orphan*/  PUNICODE_STRING ;
typedef  TYPE_6__* PFILE_OBJECT ;
typedef  TYPE_7__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ BooleanFlagOn (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ClearFlag (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  ExAcquireFastMutex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExFreeToPagedLookasideList (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  ExReleaseFastMutex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FCB_DELAYED_CLOSE ; 
 scalar_t__ FCB_DELETE_PENDING ; 
 scalar_t__ FILE_DELETE_ON_CLOSE ; 
 scalar_t__ FILE_DIRECTORY_FILE ; 
 scalar_t__ FILE_OVERWRITE ; 
 scalar_t__ FILE_OVERWRITE_IF ; 
 scalar_t__ FILE_SUPERSEDE ; 
 int /*<<< orphan*/  IOCTL_DISK_CHECK_VERIFY ; 
 int /*<<< orphan*/  IsListEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveEntryList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_ACCESS_DENIED ; 
 int /*<<< orphan*/  STATUS_CANNOT_DELETE ; 
 int /*<<< orphan*/  STATUS_DELETE_PENDING ; 
 int /*<<< orphan*/  STATUS_OBJECT_NAME_COLLISION ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VfatBlockDeviceIoControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_24__* VfatGlobalData ; 
 int /*<<< orphan*/  vfatAttachFCBToFileObject (TYPE_7__*,TYPE_5__*,TYPE_6__*) ; 
 scalar_t__ vfatFCBIsDirectory (TYPE_5__*) ; 
 scalar_t__ vfatFCBIsReadOnly (TYPE_5__*) ; 
 scalar_t__ vfatFCBIsRoot (TYPE_5__*) ; 
 int /*<<< orphan*/  vfatGetFCBForFile (TYPE_7__*,TYPE_5__**,TYPE_5__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfatGrabFCB (TYPE_7__*,TYPE_5__*) ; 
 int /*<<< orphan*/  vfatReleaseFCB (TYPE_7__*,TYPE_5__*) ; 

__attribute__((used)) static
NTSTATUS
VfatOpenFile(
    PDEVICE_EXTENSION DeviceExt,
    PUNICODE_STRING PathNameU,
    PFILE_OBJECT FileObject,
    ULONG RequestedDisposition,
    ULONG RequestedOptions,
    PVFATFCB *ParentFcb)
{
    PVFATFCB Fcb;
    NTSTATUS Status;

    DPRINT("VfatOpenFile(%p, '%wZ', %p, %p)\n", DeviceExt, PathNameU, FileObject, ParentFcb);

    if (FileObject->RelatedFileObject)
    {
        DPRINT("'%wZ'\n", &FileObject->RelatedFileObject->FileName);

        *ParentFcb = FileObject->RelatedFileObject->FsContext;
    }
    else
    {
        *ParentFcb = NULL;
    }

    if (!DeviceExt->FatInfo.FixedMedia)
    {
        Status = VfatBlockDeviceIoControl(DeviceExt->StorageDevice,
                                          IOCTL_DISK_CHECK_VERIFY,
                                          NULL,
                                          0,
                                          NULL,
                                          0,
                                          FALSE);
        if (!NT_SUCCESS(Status))
        {
            DPRINT("Status %lx\n", Status);
            *ParentFcb = NULL;
            return Status;
        }
    }

    if (*ParentFcb)
    {
        vfatGrabFCB(DeviceExt, *ParentFcb);
    }

    /*  try first to find an existing FCB in memory  */
    DPRINT("Checking for existing FCB in memory\n");

    Status = vfatGetFCBForFile(DeviceExt, ParentFcb, &Fcb, PathNameU);
    if (!NT_SUCCESS(Status))
    {
        DPRINT ("Could not make a new FCB, status: %x\n", Status);
        return  Status;
    }

    /* Fail, if we try to overwrite an existing directory */
    if ((!BooleanFlagOn(RequestedOptions, FILE_DIRECTORY_FILE) && vfatFCBIsDirectory(Fcb)) &&
        (RequestedDisposition == FILE_OVERWRITE ||
         RequestedDisposition == FILE_OVERWRITE_IF ||
         RequestedDisposition == FILE_SUPERSEDE))
    {
        vfatReleaseFCB(DeviceExt, Fcb);
        return STATUS_OBJECT_NAME_COLLISION;
    }

    if (BooleanFlagOn(Fcb->Flags, FCB_DELETE_PENDING))
    {
        vfatReleaseFCB(DeviceExt, Fcb);
        return STATUS_DELETE_PENDING;
    }

    /* Fail, if we try to overwrite a read-only file */
    if (vfatFCBIsReadOnly(Fcb) &&
        (RequestedDisposition == FILE_OVERWRITE ||
         RequestedDisposition == FILE_OVERWRITE_IF))
    {
        vfatReleaseFCB(DeviceExt, Fcb);
        return STATUS_ACCESS_DENIED;
    }

    if (vfatFCBIsReadOnly(Fcb) &&
        (RequestedOptions & FILE_DELETE_ON_CLOSE))
    {
        vfatReleaseFCB(DeviceExt, Fcb);
        return STATUS_CANNOT_DELETE;
    }

    if ((vfatFCBIsRoot(Fcb) ||
         (Fcb->LongNameU.Length == sizeof(WCHAR) && Fcb->LongNameU.Buffer[0] == L'.') ||
         (Fcb->LongNameU.Length == 2 * sizeof(WCHAR) && Fcb->LongNameU.Buffer[0] == L'.' && Fcb->LongNameU.Buffer[1] == L'.')) &&
        BooleanFlagOn(RequestedOptions, FILE_DELETE_ON_CLOSE))
    {
        // we cannot delete a '.', '..' or the root directory
        vfatReleaseFCB(DeviceExt, Fcb);
        return STATUS_CANNOT_DELETE;
    }

    /* If that one was marked for closing, remove it */
    if (BooleanFlagOn(Fcb->Flags, FCB_DELAYED_CLOSE))
    {
        BOOLEAN ConcurrentDeletion;
        PVFAT_CLOSE_CONTEXT CloseContext;

        /* Get the context */
        CloseContext = Fcb->CloseContext;
        /* Is someone already taking over? */
        if (CloseContext != NULL)
        {
            ConcurrentDeletion = FALSE;
            /* Lock list */
            ExAcquireFastMutex(&VfatGlobalData->CloseMutex);
            /* Check whether it was already removed, if not, do it */
            if (!IsListEmpty(&CloseContext->CloseListEntry))
            {
                RemoveEntryList(&CloseContext->CloseListEntry);
                --VfatGlobalData->CloseCount;
                ConcurrentDeletion = TRUE;
            }
            ExReleaseFastMutex(&VfatGlobalData->CloseMutex);

            /* It's not delayed anymore! */
            ClearFlag(Fcb->Flags, FCB_DELAYED_CLOSE);
            /* Release the extra reference (would have been removed by IRP_MJ_CLOSE) */
            vfatReleaseFCB(DeviceExt, Fcb);
            Fcb->CloseContext = NULL;
            /* If no concurrent deletion, free work item */
            if (!ConcurrentDeletion)
            {
                ExFreeToPagedLookasideList(&VfatGlobalData->CloseContextLookasideList, CloseContext);
            }
        }

        DPRINT("Reusing delayed close FCB for %wZ\n", &Fcb->PathNameU);
    }

    DPRINT("Attaching FCB to fileObject\n");
    Status = vfatAttachFCBToFileObject(DeviceExt, Fcb, FileObject);
    if (!NT_SUCCESS(Status))
    {
        vfatReleaseFCB(DeviceExt, Fcb);
    }
    return  Status;
}