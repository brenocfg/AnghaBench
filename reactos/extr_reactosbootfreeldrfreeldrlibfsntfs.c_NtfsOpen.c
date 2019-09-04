#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ULONG ;
struct TYPE_10__ {int /*<<< orphan*/  DataContext; TYPE_1__* Volume; } ;
struct TYPE_9__ {scalar_t__ MftRecordSize; } ;
typedef  TYPE_1__* PNTFS_VOLUME_INFO ;
typedef  scalar_t__ PNTFS_MFT_RECORD ;
typedef  TYPE_2__* PNTFS_FILE_HANDLE ;
typedef  scalar_t__ OPENMODE ;
typedef  int /*<<< orphan*/  NTFS_FILE_HANDLE ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int /*<<< orphan*/  ARC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ESUCCESS ; 
 TYPE_2__* FrLdrTempAlloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrLdrTempFree (TYPE_2__*,int /*<<< orphan*/ ) ; 
 size_t FsGetDeviceId (size_t) ; 
 int /*<<< orphan*/  FsSetDeviceSpecific (size_t,TYPE_2__*) ; 
 int /*<<< orphan*/  NtfsLookupFile (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_1__** NtfsVolumes ; 
 scalar_t__ OpenReadOnly ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  TAG_NTFS_FILE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *) ; 

ARC_STATUS NtfsOpen(CHAR* Path, OPENMODE OpenMode, ULONG* FileId)
{
    PNTFS_VOLUME_INFO Volume;
    PNTFS_FILE_HANDLE FileHandle;
    PNTFS_MFT_RECORD MftRecord;
    ULONG DeviceId;

    //
    // Check parameters
    //
    if (OpenMode != OpenReadOnly)
        return EACCES;

    //
    // Get underlying device
    //
    DeviceId = FsGetDeviceId(*FileId);
    Volume = NtfsVolumes[DeviceId];

    TRACE("NtfsOpen() FileName = %s\n", Path);

    //
    // Allocate file structure
    //
    FileHandle = FrLdrTempAlloc(sizeof(NTFS_FILE_HANDLE) + Volume->MftRecordSize,
                                TAG_NTFS_FILE);
    if (!FileHandle)
    {
        return ENOMEM;
    }
    RtlZeroMemory(FileHandle, sizeof(NTFS_FILE_HANDLE) + Volume->MftRecordSize);
    FileHandle->Volume = Volume;

    //
    // Search file entry
    //
    MftRecord = (PNTFS_MFT_RECORD)(FileHandle + 1);
    if (!NtfsLookupFile(Volume, Path, MftRecord, &FileHandle->DataContext))
    {
        FrLdrTempFree(FileHandle, TAG_NTFS_FILE);
        return ENOENT;
    }

    FsSetDeviceSpecific(*FileId, FileHandle);
    return ESUCCESS;
}