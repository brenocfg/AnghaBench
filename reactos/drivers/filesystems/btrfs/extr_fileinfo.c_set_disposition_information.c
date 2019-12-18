#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_14__ ;
typedef  struct TYPE_23__   TYPE_13__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
struct TYPE_32__ {scalar_t__ fcb; int delete_on_close; int posix_delete; TYPE_3__* parent; } ;
typedef  TYPE_8__ file_ref ;
struct TYPE_31__ {int /*<<< orphan*/  Resource; } ;
struct TYPE_29__ {scalar_t__ st_size; } ;
struct TYPE_33__ {int atts; scalar_t__ inode; scalar_t__ type; TYPE_7__ Header; TYPE_6__* nonpaged; TYPE_5__ inode_item; TYPE_4__* subvol; scalar_t__ ads; } ;
typedef  TYPE_9__ fcb ;
struct TYPE_20__ {scalar_t__ dummy_fcb; int /*<<< orphan*/  DirNotifyList; int /*<<< orphan*/  NotifySync; } ;
typedef  TYPE_10__ device_extension ;
struct TYPE_21__ {TYPE_8__* fileref; } ;
typedef  TYPE_11__ ccb ;
typedef  int ULONG ;
struct TYPE_30__ {int /*<<< orphan*/  segment_object; } ;
struct TYPE_28__ {scalar_t__ id; } ;
struct TYPE_27__ {TYPE_2__* fcb; } ;
struct TYPE_26__ {int atts; } ;
struct TYPE_25__ {TYPE_14__* SystemBuffer; } ;
struct TYPE_24__ {int Flags; scalar_t__ DeleteFile; } ;
struct TYPE_23__ {int DeletePending; TYPE_9__* FsContext; TYPE_11__* FsContext2; } ;
struct TYPE_22__ {TYPE_1__ AssociatedIrp; } ;
typedef  TYPE_12__* PIRP ;
typedef  TYPE_13__* PFILE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_14__ FILE_DISPOSITION_INFORMATION_EX ;
typedef  TYPE_14__ FILE_DISPOSITION_INFORMATION ;

/* Variables and functions */
 scalar_t__ BTRFS_ROOT_FSTREE ; 
 scalar_t__ BTRFS_TYPE_DIRECTORY ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ ) ; 
 int FILE_ATTRIBUTE_READONLY ; 
 int FILE_DISPOSITION_DELETE ; 
 int FILE_DISPOSITION_FORCE_IMAGE_SECTION_CHECK ; 
 int FILE_DISPOSITION_POSIX_SEMANTICS ; 
 int /*<<< orphan*/  FsRtlNotifyFullChangeDirectory (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_9__*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MmFlushForDelete ; 
 int /*<<< orphan*/  MmFlushImageSection (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_ACCESS_DENIED ; 
 int /*<<< orphan*/  STATUS_CANNOT_DELETE ; 
 int /*<<< orphan*/  STATUS_DIRECTORY_NOT_EMPTY ; 
 int /*<<< orphan*/  STATUS_INTERNAL_ERROR ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ SUBVOL_ROOT_INODE ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WARN (char*) ; 

__attribute__((used)) static NTSTATUS set_disposition_information(device_extension* Vcb, PIRP Irp, PFILE_OBJECT FileObject, bool ex) {
    fcb* fcb = FileObject->FsContext;
    ccb* ccb = FileObject->FsContext2;
    file_ref* fileref = ccb ? ccb->fileref : NULL;
    ULONG atts, flags;
    NTSTATUS Status;

    if (!fileref)
        return STATUS_INVALID_PARAMETER;

    if (ex) {
        FILE_DISPOSITION_INFORMATION_EX* fdi = Irp->AssociatedIrp.SystemBuffer;

        flags = fdi->Flags;
    } else {
        FILE_DISPOSITION_INFORMATION* fdi = Irp->AssociatedIrp.SystemBuffer;

        flags = fdi->DeleteFile ? FILE_DISPOSITION_DELETE : 0;
    }

    ExAcquireResourceExclusiveLite(fcb->Header.Resource, true);

    TRACE("changing delete_on_close to %s for fcb %p\n", flags & FILE_DISPOSITION_DELETE ? "true" : "false", fcb);

    if (fcb->ads) {
        if (fileref->parent)
            atts = fileref->parent->fcb->atts;
        else {
            ERR("no fileref for stream\n");
            Status = STATUS_INTERNAL_ERROR;
            goto end;
        }
    } else
        atts = fcb->atts;

    TRACE("atts = %x\n", atts);

    if (atts & FILE_ATTRIBUTE_READONLY) {
        TRACE("not allowing readonly file to be deleted\n");
        Status = STATUS_CANNOT_DELETE;
        goto end;
    }

    if (fcb->inode == SUBVOL_ROOT_INODE && fcb->subvol->id == BTRFS_ROOT_FSTREE) {
        WARN("not allowing \\$Root to be deleted\n");
        Status = STATUS_ACCESS_DENIED;
        goto end;
    }

    // FIXME - can we skip this bit for subvols?
    if (fcb->type == BTRFS_TYPE_DIRECTORY && fcb->inode_item.st_size > 0 && (!fileref || fileref->fcb != Vcb->dummy_fcb)) {
        TRACE("directory not empty\n");
        Status = STATUS_DIRECTORY_NOT_EMPTY;
        goto end;
    }

    if (!MmFlushImageSection(&fcb->nonpaged->segment_object, MmFlushForDelete)) {
        if (!ex || flags & FILE_DISPOSITION_FORCE_IMAGE_SECTION_CHECK) {
            TRACE("trying to delete file which is being mapped as an image\n");
            Status = STATUS_CANNOT_DELETE;
            goto end;
        }
    }

    ccb->fileref->delete_on_close = flags & FILE_DISPOSITION_DELETE;

    FileObject->DeletePending = flags & FILE_DISPOSITION_DELETE;

    if (flags & FILE_DISPOSITION_DELETE && flags & FILE_DISPOSITION_POSIX_SEMANTICS)
        ccb->fileref->posix_delete = true;

    Status = STATUS_SUCCESS;

end:
    ExReleaseResourceLite(fcb->Header.Resource);

    // send notification that directory is about to be deleted
    if (NT_SUCCESS(Status) && flags & FILE_DISPOSITION_DELETE && fcb->type == BTRFS_TYPE_DIRECTORY) {
        FsRtlNotifyFullChangeDirectory(Vcb->NotifySync, &Vcb->DirNotifyList, FileObject->FsContext,
                                       NULL, false, false, 0, NULL, NULL, NULL);
    }

    return Status;
}