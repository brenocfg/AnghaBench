#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int ULONGLONG ;
struct TYPE_14__ {int /*<<< orphan*/  FileRecLookasideList; } ;
struct TYPE_13__ {int Flags; } ;
typedef  int /*<<< orphan*/ * PNTFS_FCB ;
typedef  TYPE_1__* PFILE_RECORD_HEADER ;
typedef  int /*<<< orphan*/  PFILE_OBJECT ;
typedef  TYPE_2__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DPRINT (char*,TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 TYPE_1__* ExAllocateFromNPagedLookasideList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExFreeToNPagedLookasideList (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int FRH_IN_USE ; 
 int /*<<< orphan*/ * MftIdToName ; 
 int NTFS_FILE_FIRST_USER_FILE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtfsAttachFCBToFileObject (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NtfsGrabFCBFromTable (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtfsMakeFCBFromDirEntry (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ReadFileRecord (TYPE_2__*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_OBJECT_NAME_NOT_FOUND ; 
 int /*<<< orphan*/  STATUS_OBJECT_PATH_NOT_FOUND ; 

__attribute__((used)) static
NTSTATUS
NtfsOpenFileById(PDEVICE_EXTENSION DeviceExt,
                 PFILE_OBJECT FileObject,
                 ULONGLONG MftId,
                 PNTFS_FCB * FoundFCB)
{
    NTSTATUS Status;
    PNTFS_FCB FCB;
    PFILE_RECORD_HEADER MftRecord;

    DPRINT("NtfsOpenFileById(%p, %p, %I64x, %p)\n", DeviceExt, FileObject, MftId, FoundFCB);

    ASSERT(MftId < NTFS_FILE_FIRST_USER_FILE);
    if (MftId > 0xb) /* No entries are used yet beyond this */
    {
        return STATUS_OBJECT_NAME_NOT_FOUND;
    }

    MftRecord = ExAllocateFromNPagedLookasideList(&DeviceExt->FileRecLookasideList);
    if (MftRecord == NULL)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    Status = ReadFileRecord(DeviceExt, MftId, MftRecord);
    if (!NT_SUCCESS(Status))
    {
        ExFreeToNPagedLookasideList(&DeviceExt->FileRecLookasideList, MftRecord);
        return Status;
    }

    if (!(MftRecord->Flags & FRH_IN_USE))
    {
        ExFreeToNPagedLookasideList(&DeviceExt->FileRecLookasideList, MftRecord);
        return STATUS_OBJECT_PATH_NOT_FOUND;
    }

    FCB = NtfsGrabFCBFromTable(DeviceExt, MftIdToName[MftId]);
    if (FCB == NULL)
    {
        UNICODE_STRING Name;

        RtlInitUnicodeString(&Name, MftIdToName[MftId]);
        Status = NtfsMakeFCBFromDirEntry(DeviceExt, NULL, &Name, NULL, MftRecord, MftId, &FCB);
        if (!NT_SUCCESS(Status))
        {
            ExFreeToNPagedLookasideList(&DeviceExt->FileRecLookasideList, MftRecord);
            return Status;
        }
    }

    ASSERT(FCB != NULL);

    ExFreeToNPagedLookasideList(&DeviceExt->FileRecLookasideList, MftRecord);

    Status = NtfsAttachFCBToFileObject(DeviceExt,
                                       FCB,
                                       FileObject);
    *FoundFCB = FCB;

    return Status;
}