#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_28__ {int Length; int MaximumLength; scalar_t__ Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ ULONGLONG ;
typedef  scalar_t__ ULONG ;
struct TYPE_33__ {scalar_t__ QuadPart; } ;
struct TYPE_32__ {scalar_t__ FsContext; } ;
struct TYPE_31__ {int /*<<< orphan*/  pRecord; } ;
struct TYPE_30__ {scalar_t__ Type; int NameLength; scalar_t__ NameOffset; } ;
struct TYPE_29__ {int Flags; scalar_t__ DirectoryFileReferenceNumber; int NameLength; int /*<<< orphan*/  FileRecLookasideList; int /*<<< orphan*/  Vcb; scalar_t__ Name; int /*<<< orphan*/  Stream; int /*<<< orphan*/  ObjectName; int /*<<< orphan*/  MFTIndex; int /*<<< orphan*/  PathName; } ;
typedef  scalar_t__ PWCHAR ;
typedef  scalar_t__* PULONG ;
typedef  int /*<<< orphan*/ * PUCHAR ;
typedef  TYPE_2__* PNTFS_FCB ;
typedef  TYPE_3__* PNTFS_ATTR_RECORD ;
typedef  TYPE_4__* PNTFS_ATTR_CONTEXT ;
typedef  int /*<<< orphan*/ * PFILE_RECORD_HEADER ;
typedef  TYPE_5__* PFILE_OBJECT ;
typedef  TYPE_2__* PFILENAME_ATTRIBUTE ;
typedef  TYPE_2__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_8__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  FIND_ATTR_CONTXT ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_2__*) ; 
 scalar_t__ AttributeAllocatedLength (int /*<<< orphan*/ ) ; 
 scalar_t__ AttributeData ; 
 scalar_t__ AttributeDataLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 int /*<<< orphan*/ * ExAllocateFromNPagedLookasideList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExFreeToNPagedLookasideList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int FCB_IS_VOLUME ; 
 int /*<<< orphan*/  FindAttribute (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__**,scalar_t__*) ; 
 int /*<<< orphan*/  FindCloseAttribute (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FindFirstAttribute (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  FindNextAttribute (int /*<<< orphan*/ *,TYPE_3__**) ; 
 TYPE_2__* GetBestFileNameFromRecord (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IRP_PAGING_IO ; 
 scalar_t__ NTFS_MFT_MASK ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 scalar_t__ NtfsFCBIsCompressed (TYPE_2__*) ; 
 int /*<<< orphan*/  ReadFileRecord (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseAttributeContext (TYPE_4__*) ; 
 int /*<<< orphan*/  STATUS_ACCESS_DENIED ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_UNEXPECTED_IO_ERROR ; 
 int /*<<< orphan*/  SetAttributeDataLength (TYPE_5__*,TYPE_2__*,TYPE_4__*,scalar_t__,int /*<<< orphan*/ *,TYPE_8__*) ; 
 int /*<<< orphan*/  UNIMPLEMENTED ; 
 int /*<<< orphan*/  UpdateFileNameRecord (int /*<<< orphan*/ ,scalar_t__,TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  WriteAttribute (TYPE_2__*,TYPE_4__*,scalar_t__,int /*<<< orphan*/ * const,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcslen (int /*<<< orphan*/ ) ; 

NTSTATUS NtfsWriteFile(PDEVICE_EXTENSION DeviceExt,
                       PFILE_OBJECT FileObject,
                       const PUCHAR Buffer,
                       ULONG Length,
                       ULONG WriteOffset,
                       ULONG IrpFlags,
                       BOOLEAN CaseSensitive,
                       PULONG LengthWritten)
{
    NTSTATUS Status = STATUS_NOT_IMPLEMENTED;
    PNTFS_FCB Fcb;
    PFILE_RECORD_HEADER FileRecord;
    PNTFS_ATTR_CONTEXT DataContext;
    ULONG AttributeOffset;
    ULONGLONG StreamSize;

    DPRINT("NtfsWriteFile(%p, %p, %p, %lu, %lu, %x, %s, %p)\n",
           DeviceExt,
           FileObject,
           Buffer,
           Length,
           WriteOffset,
           IrpFlags,
           (CaseSensitive ? "TRUE" : "FALSE"),
           LengthWritten);

    *LengthWritten = 0;

    ASSERT(DeviceExt);

    if (Length == 0)
    {
        if (Buffer == NULL)
            return STATUS_SUCCESS;
        else
            return STATUS_INVALID_PARAMETER;
    }

    // get the File control block
    Fcb = (PNTFS_FCB)FileObject->FsContext;
    ASSERT(Fcb);

    DPRINT("Fcb->PathName: %wS\n", Fcb->PathName);
    DPRINT("Fcb->ObjectName: %wS\n", Fcb->ObjectName);

    // we don't yet handle compression
    if (NtfsFCBIsCompressed(Fcb))
    {
        DPRINT("Compressed file!\n");
        UNIMPLEMENTED;
        return STATUS_NOT_IMPLEMENTED;
    }

    // allocate non-paged memory for the FILE_RECORD_HEADER
    FileRecord = ExAllocateFromNPagedLookasideList(&DeviceExt->FileRecLookasideList);
    if (FileRecord == NULL)
    {
        DPRINT1("Not enough memory! Can't write %wS!\n", Fcb->PathName);
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    // read the FILE_RECORD_HEADER from the drive (or cache)
    DPRINT("Reading file record...\n");
    Status = ReadFileRecord(DeviceExt, Fcb->MFTIndex, FileRecord);
    if (!NT_SUCCESS(Status))
    {
        // We couldn't get the file's record. Free the memory and return the error
        DPRINT1("Can't find record for %wS!\n", Fcb->ObjectName);
        ExFreeToNPagedLookasideList(&DeviceExt->FileRecLookasideList, FileRecord);
        return Status;
    }

    DPRINT("Found record for %wS\n", Fcb->ObjectName);

    // Find the attribute with the data stream for our file
    DPRINT("Finding Data Attribute...\n");
    Status = FindAttribute(DeviceExt, FileRecord, AttributeData, Fcb->Stream, wcslen(Fcb->Stream), &DataContext,
                           &AttributeOffset);

    // Did we fail to find the attribute?
    if (!NT_SUCCESS(Status))
    {
        NTSTATUS BrowseStatus;
        FIND_ATTR_CONTXT Context;
        PNTFS_ATTR_RECORD Attribute;

        DPRINT1("No '%S' data stream associated with file!\n", Fcb->Stream);

        // Couldn't find the requested data stream; print a list of streams available
        BrowseStatus = FindFirstAttribute(&Context, DeviceExt, FileRecord, FALSE, &Attribute);
        while (NT_SUCCESS(BrowseStatus))
        {
            if (Attribute->Type == AttributeData)
            {
                UNICODE_STRING Name;

                Name.Length = Attribute->NameLength * sizeof(WCHAR);
                Name.MaximumLength = Name.Length;
                Name.Buffer = (PWCHAR)((ULONG_PTR)Attribute + Attribute->NameOffset);
                DPRINT1("Data stream: '%wZ' available\n", &Name);
            }

            BrowseStatus = FindNextAttribute(&Context, &Attribute);
        }
        FindCloseAttribute(&Context);

        ReleaseAttributeContext(DataContext);
        ExFreeToNPagedLookasideList(&DeviceExt->FileRecLookasideList, FileRecord);
        return Status;
    }

    // Get the size of the stream on disk
    StreamSize = AttributeDataLength(DataContext->pRecord);

    DPRINT("WriteOffset: %lu\tStreamSize: %I64u\n", WriteOffset, StreamSize);

    // Are we trying to write beyond the end of the stream?
    if (WriteOffset + Length > StreamSize)
    {
        // is increasing the stream size allowed?
        if (!(Fcb->Flags & FCB_IS_VOLUME) &&
            !(IrpFlags & IRP_PAGING_IO))
        {
            LARGE_INTEGER DataSize;
            ULONGLONG AllocationSize;
            PFILENAME_ATTRIBUTE fileNameAttribute;
            ULONGLONG ParentMFTId;
            UNICODE_STRING filename;

            DataSize.QuadPart = WriteOffset + Length;

            // set the attribute data length
            Status = SetAttributeDataLength(FileObject, Fcb, DataContext, AttributeOffset, FileRecord, &DataSize);
            if (!NT_SUCCESS(Status))
            {
                ReleaseAttributeContext(DataContext);
                ExFreeToNPagedLookasideList(&DeviceExt->FileRecLookasideList, FileRecord);
                *LengthWritten = 0;
                return Status;
            }

            AllocationSize = AttributeAllocatedLength(DataContext->pRecord);

            // now we need to update this file's size in every directory index entry that references it
            // TODO: put this code in its own function and adapt it to work with every filename / hardlink
            // stored in the file record.
            fileNameAttribute = GetBestFileNameFromRecord(Fcb->Vcb, FileRecord);
            ASSERT(fileNameAttribute);

            ParentMFTId = fileNameAttribute->DirectoryFileReferenceNumber & NTFS_MFT_MASK;

            filename.Buffer = fileNameAttribute->Name;
            filename.Length = fileNameAttribute->NameLength * sizeof(WCHAR);
            filename.MaximumLength = filename.Length;

            Status = UpdateFileNameRecord(Fcb->Vcb,
                                          ParentMFTId,
                                          &filename,
                                          FALSE,
                                          DataSize.QuadPart,
                                          AllocationSize,
                                          CaseSensitive);

        }
        else
        {
            // TODO - just fail for now
            ReleaseAttributeContext(DataContext);
            ExFreeToNPagedLookasideList(&DeviceExt->FileRecLookasideList, FileRecord);
            *LengthWritten = 0;
            return STATUS_ACCESS_DENIED;
        }
    }

    DPRINT("Length: %lu\tWriteOffset: %lu\tStreamSize: %I64u\n", Length, WriteOffset, StreamSize);

    // Write the data to the attribute
    Status = WriteAttribute(DeviceExt, DataContext, WriteOffset, Buffer, Length, LengthWritten, FileRecord);

    // Did the write fail?
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("Write failure!\n");
        ReleaseAttributeContext(DataContext);
        ExFreeToNPagedLookasideList(&DeviceExt->FileRecLookasideList, FileRecord);

        return Status;
    }

    // This should never happen:
    if (*LengthWritten != Length)
    {
        DPRINT1("\a\tNTFS DRIVER ERROR: length written (%lu) differs from requested (%lu), but no error was indicated!\n",
            *LengthWritten, Length);
        Status = STATUS_UNEXPECTED_IO_ERROR;
    }

    ReleaseAttributeContext(DataContext);
    ExFreeToNPagedLookasideList(&DeviceExt->FileRecLookasideList, FileRecord);

    return Status;
}