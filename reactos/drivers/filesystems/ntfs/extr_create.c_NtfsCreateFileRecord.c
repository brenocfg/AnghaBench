#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ ULONGLONG ;
struct TYPE_25__ {int /*<<< orphan*/  FileRecLookasideList; } ;
struct TYPE_24__ {scalar_t__ SequenceNumber; scalar_t__ AttributeOffset; } ;
struct TYPE_22__ {scalar_t__ ValueOffset; } ;
struct TYPE_23__ {scalar_t__ Length; TYPE_1__ Resident; } ;
typedef  TYPE_2__* PNTFS_ATTR_RECORD ;
typedef  TYPE_3__* PFILE_RECORD_HEADER ;
typedef  int /*<<< orphan*/  PFILE_OBJECT ;
typedef  scalar_t__ PFILENAME_ATTRIBUTE ;
typedef  TYPE_4__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  AddData (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  AddFileName (TYPE_3__*,TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  AddNewMftEntry (TYPE_3__*,TYPE_4__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AddStandardInformation (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  DPRINT (char*,TYPE_4__*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 int /*<<< orphan*/  ExFreeToNPagedLookasideList (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ NTFS_FILE_ROOT ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtfsAddFilenameToDirectory (TYPE_4__*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_3__* NtfsCreateEmptyFileRecord (TYPE_4__*) ; 
 int /*<<< orphan*/  NtfsDumpFileRecord (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS
NtfsCreateFileRecord(PDEVICE_EXTENSION DeviceExt,
                     PFILE_OBJECT FileObject,
                     BOOLEAN CaseSensitive,
                     BOOLEAN CanWait)
{
    NTSTATUS Status = STATUS_SUCCESS;
    PFILE_RECORD_HEADER FileRecord;
    PNTFS_ATTR_RECORD NextAttribute;
    PFILENAME_ATTRIBUTE FilenameAttribute;
    ULONGLONG ParentMftIndex;
    ULONGLONG FileMftIndex;

    DPRINT("NtfsCreateFileRecord(%p, %p, %s, %s)\n",
            DeviceExt,
            FileObject,
            CaseSensitive ? "TRUE" : "FALSE",
            CanWait ? "TRUE" : "FALSE");

    // allocate memory for file record
    FileRecord = NtfsCreateEmptyFileRecord(DeviceExt);
    if (!FileRecord)
    {
        DPRINT1("ERROR: Unable to allocate memory for file record!\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    // find where the first attribute will be added
    NextAttribute = (PNTFS_ATTR_RECORD)((ULONG_PTR)FileRecord + FileRecord->AttributeOffset);

    // add first attribute, $STANDARD_INFORMATION
    AddStandardInformation(FileRecord, NextAttribute);

    // advance NextAttribute pointer to the next attribute
    NextAttribute = (PNTFS_ATTR_RECORD)((ULONG_PTR)NextAttribute + (ULONG_PTR)NextAttribute->Length);

    // Add the $FILE_NAME attribute
    AddFileName(FileRecord, NextAttribute, DeviceExt, FileObject, CaseSensitive, &ParentMftIndex);

    // save a pointer to the filename attribute
    FilenameAttribute = (PFILENAME_ATTRIBUTE)((ULONG_PTR)NextAttribute + NextAttribute->Resident.ValueOffset);

    // advance NextAttribute pointer to the next attribute
    NextAttribute = (PNTFS_ATTR_RECORD)((ULONG_PTR)NextAttribute + (ULONG_PTR)NextAttribute->Length);

    // add the $DATA attribute
    AddData(FileRecord, NextAttribute);

#ifndef NDEBUG
    // dump file record in memory (for debugging)
    NtfsDumpFileRecord(DeviceExt, FileRecord);
#endif

    // Now that we've built the file record in memory, we need to store it in the MFT.
    Status = AddNewMftEntry(FileRecord, DeviceExt, &FileMftIndex, CanWait);
    if (NT_SUCCESS(Status))
    {
        // The highest 2 bytes should be the sequence number, unless the parent happens to be root
        if (FileMftIndex == NTFS_FILE_ROOT)
            FileMftIndex = FileMftIndex + ((ULONGLONG)NTFS_FILE_ROOT << 48);
        else
            FileMftIndex = FileMftIndex + ((ULONGLONG)FileRecord->SequenceNumber << 48);

        DPRINT1("New File Reference: 0x%016I64x\n", FileMftIndex);

        // Add the filename attribute to the filename-index of the parent directory
        Status = NtfsAddFilenameToDirectory(DeviceExt,
                                            ParentMftIndex,
                                            FileMftIndex,
                                            FilenameAttribute,
                                            CaseSensitive);
    }

    ExFreeToNPagedLookasideList(&DeviceExt->FileRecLookasideList, FileRecord);

    return Status;
}