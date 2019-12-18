#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_47__   TYPE_9__ ;
typedef  struct TYPE_46__   TYPE_8__ ;
typedef  struct TYPE_45__   TYPE_7__ ;
typedef  struct TYPE_44__   TYPE_6__ ;
typedef  struct TYPE_43__   TYPE_5__ ;
typedef  struct TYPE_42__   TYPE_4__ ;
typedef  struct TYPE_41__   TYPE_3__ ;
typedef  struct TYPE_40__   TYPE_30__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_23__ ;
typedef  struct TYPE_37__   TYPE_1__ ;
typedef  struct TYPE_36__   TYPE_18__ ;
typedef  struct TYPE_35__   TYPE_13__ ;
typedef  struct TYPE_34__   TYPE_12__ ;
typedef  struct TYPE_33__   TYPE_11__ ;
typedef  struct TYPE_32__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_40__ {int MaximumLength; int /*<<< orphan*/ * Buffer; } ;
struct TYPE_37__ {int MaximumLength; int /*<<< orphan*/ * Buffer; } ;
struct TYPE_44__ {scalar_t__ DirIndex; TYPE_30__ LongNameU; TYPE_1__ ShortNameU; TYPE_18__* DeviceExt; } ;
typedef  TYPE_6__ VFAT_DIRENTRY_CONTEXT ;
typedef  scalar_t__ ULONG ;
struct TYPE_38__ {int* Buffer; scalar_t__ MaximumLength; int Length; } ;
struct TYPE_47__ {scalar_t__ Entry; TYPE_23__ SearchPattern; } ;
struct TYPE_46__ {int /*<<< orphan*/  MainResource; } ;
struct TYPE_45__ {TYPE_18__* DeviceExt; TYPE_13__* Irp; TYPE_11__* Stack; int /*<<< orphan*/  Flags; TYPE_3__* FileObject; } ;
struct TYPE_42__ {scalar_t__ Length; int FileInformationClass; scalar_t__ FileIndex; scalar_t__ FileName; } ;
struct TYPE_43__ {TYPE_4__ QueryDirectory; } ;
struct TYPE_41__ {scalar_t__ FsContext; scalar_t__ FsContext2; } ;
struct TYPE_39__ {scalar_t__ Information; } ;
struct TYPE_36__ {int /*<<< orphan*/  DirResource; } ;
struct TYPE_35__ {scalar_t__ RequestorMode; TYPE_2__ IoStatus; int /*<<< orphan*/ * UserBuffer; int /*<<< orphan*/ * MdlAddress; } ;
struct TYPE_34__ {scalar_t__ NextEntryOffset; scalar_t__ FileIndex; } ;
struct TYPE_33__ {TYPE_5__ Parameters; int /*<<< orphan*/  Flags; } ;
struct TYPE_32__ {scalar_t__ Length; int /*<<< orphan*/ * Buffer; } ;
typedef  int /*<<< orphan*/  ShortNameBuffer ;
typedef  TYPE_7__* PVFAT_IRP_CONTEXT ;
typedef  TYPE_8__* PVFATFCB ;
typedef  TYPE_9__* PVFATCCB ;
typedef  TYPE_10__* PUNICODE_STRING ;
typedef  int /*<<< orphan*/ * PUCHAR ;
typedef  TYPE_11__* PIO_STACK_LOCATION ;
typedef  TYPE_12__* PFILE_NAMES_INFORMATION ;
typedef  int /*<<< orphan*/  PFILE_FULL_DIR_INFORMATION ;
typedef  int /*<<< orphan*/  PFILE_DIRECTORY_INFORMATION ;
typedef  int /*<<< orphan*/  PFILE_BOTH_DIR_INFORMATION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  LongNameBuffer ;
typedef  scalar_t__ LONG ;
typedef  int FILE_INFORMATION_CLASS ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ BooleanFlagOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,TYPE_30__*,TYPE_23__*,...) ; 
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ExAcquireResourceSharedLite (int /*<<< orphan*/ *,scalar_t__) ; 
 void* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
#define  FileBothDirectoryInformation 131 
#define  FileDirectoryInformation 130 
#define  FileFullDirectoryInformation 129 
#define  FileNamesInformation 128 
 int /*<<< orphan*/  FindFile (TYPE_18__*,TYPE_8__*,TYPE_23__*,TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  IRPCONTEXT_CANWAIT ; 
 int /*<<< orphan*/  IoWriteAccess ; 
 scalar_t__ KernelMode ; 
 int /*<<< orphan*/  LONGNAME_MAX_LENGTH ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  ProbeForWrite (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  RtlCopyUnicodeString (TYPE_23__*,TYPE_10__*) ; 
 int /*<<< orphan*/  SL_INDEX_SPECIFIED ; 
 int /*<<< orphan*/  SL_RESTART_SCAN ; 
 int /*<<< orphan*/  SL_RETURN_SINGLE_ENTRY ; 
 int /*<<< orphan*/  STATUS_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_INVALID_INFO_CLASS ; 
 int /*<<< orphan*/  STATUS_NO_MORE_FILES ; 
 int /*<<< orphan*/  STATUS_NO_SUCH_FILE ; 
 int /*<<< orphan*/  STATUS_PENDING ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TAG_SEARCH ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VfatGetFileBothInformation (TYPE_6__*,TYPE_18__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VfatGetFileDirectoryInformation (TYPE_6__*,TYPE_18__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VfatGetFileFullDirectoryInformation (TYPE_6__*,TYPE_18__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VfatGetFileNamesInformation (TYPE_6__*,TYPE_12__*,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * VfatGetUserBuffer (TYPE_13__*,scalar_t__) ; 
 int /*<<< orphan*/  VfatLockUserBuffer (TYPE_13__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
NTSTATUS
DoQuery(
    PVFAT_IRP_CONTEXT IrpContext)
{
    NTSTATUS Status = STATUS_SUCCESS;
    LONG BufferLength = 0;
    PUNICODE_STRING pSearchPattern = NULL;
    FILE_INFORMATION_CLASS FileInformationClass;
    PUCHAR Buffer = NULL;
    PFILE_NAMES_INFORMATION Buffer0 = NULL;
    PVFATFCB pFcb;
    PVFATCCB pCcb;
    BOOLEAN FirstQuery = FALSE;
    BOOLEAN FirstCall = TRUE;
    VFAT_DIRENTRY_CONTEXT DirContext;
    WCHAR LongNameBuffer[LONGNAME_MAX_LENGTH + 1];
    WCHAR ShortNameBuffer[13];
    ULONG Written;

    PIO_STACK_LOCATION Stack = IrpContext->Stack;

    pCcb = (PVFATCCB)IrpContext->FileObject->FsContext2;
    pFcb = (PVFATFCB)IrpContext->FileObject->FsContext;

    /* Determine Buffer for result : */
    BufferLength = Stack->Parameters.QueryDirectory.Length;
#if 0
    /* Do not probe the user buffer until SEH is available */
    if (IrpContext->Irp->RequestorMode != KernelMode &&
        IrpContext->Irp->MdlAddress == NULL &&
        IrpContext->Irp->UserBuffer != NULL)
    {
        ProbeForWrite(IrpContext->Irp->UserBuffer, BufferLength, 1);
    }
#endif
    Buffer = VfatGetUserBuffer(IrpContext->Irp, FALSE);

    if (!ExAcquireResourceExclusiveLite(&IrpContext->DeviceExt->DirResource,
                                        BooleanFlagOn(IrpContext->Flags, IRPCONTEXT_CANWAIT)))
    {
        Status = VfatLockUserBuffer(IrpContext->Irp, BufferLength, IoWriteAccess);
        if (NT_SUCCESS(Status))
            Status = STATUS_PENDING;

        return Status;
    }

    if (!ExAcquireResourceSharedLite(&pFcb->MainResource,
                                     BooleanFlagOn(IrpContext->Flags, IRPCONTEXT_CANWAIT)))
    {
        ExReleaseResourceLite(&IrpContext->DeviceExt->DirResource);
        Status = VfatLockUserBuffer(IrpContext->Irp, BufferLength, IoWriteAccess);
        if (NT_SUCCESS(Status))
            Status = STATUS_PENDING;

        return Status;
    }

    /* Obtain the callers parameters */
    pSearchPattern = (PUNICODE_STRING)Stack->Parameters.QueryDirectory.FileName;
    FileInformationClass = Stack->Parameters.QueryDirectory.FileInformationClass;

    /* Allocate search pattern in case:
     * -> We don't have one already in context
     * -> We have been given an input pattern
     * -> The pattern length is not null
     * -> The pattern buffer is not null
     * Otherwise, we'll fall later and allocate a match all (*) pattern
     */
    if (pSearchPattern &&
        pSearchPattern->Length != 0 && pSearchPattern->Buffer != NULL)
    {
        if (!pCcb->SearchPattern.Buffer)
        {
            FirstQuery = TRUE;
            pCcb->SearchPattern.MaximumLength = pSearchPattern->Length + sizeof(WCHAR);
            pCcb->SearchPattern.Buffer = ExAllocatePoolWithTag(NonPagedPool,
                                                               pCcb->SearchPattern.MaximumLength,
                                                               TAG_SEARCH);
            if (!pCcb->SearchPattern.Buffer)
            {
                ExReleaseResourceLite(&pFcb->MainResource);
                ExReleaseResourceLite(&IrpContext->DeviceExt->DirResource);
                return STATUS_INSUFFICIENT_RESOURCES;
            }
            RtlCopyUnicodeString(&pCcb->SearchPattern, pSearchPattern);
            pCcb->SearchPattern.Buffer[pCcb->SearchPattern.Length / sizeof(WCHAR)] = 0;
        }
    }
    else if (!pCcb->SearchPattern.Buffer)
    {
        FirstQuery = TRUE;
        pCcb->SearchPattern.MaximumLength = 2 * sizeof(WCHAR);
        pCcb->SearchPattern.Buffer = ExAllocatePoolWithTag(NonPagedPool,
                                                           2 * sizeof(WCHAR),
                                                           TAG_SEARCH);
        if (!pCcb->SearchPattern.Buffer)
        {
            ExReleaseResourceLite(&pFcb->MainResource);
            ExReleaseResourceLite(&IrpContext->DeviceExt->DirResource);
            return STATUS_INSUFFICIENT_RESOURCES;
        }
        pCcb->SearchPattern.Buffer[0] = L'*';
        pCcb->SearchPattern.Buffer[1] = 0;
        pCcb->SearchPattern.Length = sizeof(WCHAR);
    }

    if (BooleanFlagOn(IrpContext->Stack->Flags, SL_INDEX_SPECIFIED))
    {
        DirContext.DirIndex = pCcb->Entry = Stack->Parameters.QueryDirectory.FileIndex;
    }
    else if (FirstQuery || BooleanFlagOn(IrpContext->Stack->Flags, SL_RESTART_SCAN))
    {
        DirContext.DirIndex = pCcb->Entry = 0;
    }
    else
    {
        DirContext.DirIndex = pCcb->Entry;
    }

    DPRINT("Buffer=%p tofind=%wZ\n", Buffer, &pCcb->SearchPattern);

    DirContext.DeviceExt = IrpContext->DeviceExt;
    DirContext.LongNameU.Buffer = LongNameBuffer;
    DirContext.LongNameU.MaximumLength = sizeof(LongNameBuffer);
    DirContext.ShortNameU.Buffer = ShortNameBuffer;
    DirContext.ShortNameU.MaximumLength = sizeof(ShortNameBuffer);

    Written = 0;
    while ((Status == STATUS_SUCCESS) && (BufferLength > 0))
    {
        Status = FindFile(IrpContext->DeviceExt,
                          pFcb,
                          &pCcb->SearchPattern,
                          &DirContext,
                          FirstCall);
        pCcb->Entry = DirContext.DirIndex;

        DPRINT("Found %wZ, Status=%x, entry %x\n", &DirContext.LongNameU, Status, pCcb->Entry);

        FirstCall = FALSE;
        if (NT_SUCCESS(Status))
        {
            switch (FileInformationClass)
            {
                case FileDirectoryInformation:
                    Status = VfatGetFileDirectoryInformation(&DirContext,
                                                             IrpContext->DeviceExt,
                                                             (PFILE_DIRECTORY_INFORMATION)Buffer,
                                                             BufferLength,
                                                             &Written,
                                                             Buffer0 == NULL);
                    break;

                case FileFullDirectoryInformation:
                    Status = VfatGetFileFullDirectoryInformation(&DirContext,
                                                                 IrpContext->DeviceExt,
                                                                 (PFILE_FULL_DIR_INFORMATION)Buffer,
                                                                 BufferLength,
                                                                 &Written,
                                                                 Buffer0 == NULL);
                    break;

                case FileBothDirectoryInformation:
                    Status = VfatGetFileBothInformation(&DirContext,
                                                        IrpContext->DeviceExt,
                                                        (PFILE_BOTH_DIR_INFORMATION)Buffer,
                                                        BufferLength,
                                                        &Written,
                                                        Buffer0 == NULL);
                    break;

                case FileNamesInformation:
                    Status = VfatGetFileNamesInformation(&DirContext,
                                                         (PFILE_NAMES_INFORMATION)Buffer,
                                                         BufferLength,
                                                         &Written,
                                                         Buffer0 == NULL);
                     break;

                default:
                    Status = STATUS_INVALID_INFO_CLASS;
                    break;
            }

            if (Status == STATUS_BUFFER_OVERFLOW || Status == STATUS_INVALID_INFO_CLASS)
                break;
        }
        else
        {
            Status = (FirstQuery ? STATUS_NO_SUCH_FILE : STATUS_NO_MORE_FILES);
            break;
        }

        Buffer0 = (PFILE_NAMES_INFORMATION) Buffer;
        Buffer0->FileIndex = DirContext.DirIndex;
        pCcb->Entry = ++DirContext.DirIndex;
        BufferLength -= Buffer0->NextEntryOffset;

        if (BooleanFlagOn(IrpContext->Stack->Flags, SL_RETURN_SINGLE_ENTRY))
            break;

        Buffer += Buffer0->NextEntryOffset;
    }

    if (Buffer0)
    {
        Buffer0->NextEntryOffset = 0;
        Status = STATUS_SUCCESS;
        IrpContext->Irp->IoStatus.Information = Stack->Parameters.QueryDirectory.Length - BufferLength;
    }
    else
    {
        ASSERT(Status != STATUS_SUCCESS || BufferLength == 0);
        ASSERT(Written <= Stack->Parameters.QueryDirectory.Length);
        IrpContext->Irp->IoStatus.Information = Written;
    }

    ExReleaseResourceLite(&pFcb->MainResource);
    ExReleaseResourceLite(&IrpContext->DeviceExt->DirResource);

    return Status;
}