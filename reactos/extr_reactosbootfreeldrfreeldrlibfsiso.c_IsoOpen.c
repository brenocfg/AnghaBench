#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  TempFileInfo ;
typedef  int /*<<< orphan*/  PISO_FILE_INFO ;
typedef  scalar_t__ OPENMODE ;
typedef  int /*<<< orphan*/  ISO_FILE_INFO ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  scalar_t__ ARC_STATUS ;

/* Variables and functions */
 scalar_t__ EACCES ; 
 scalar_t__ ENOENT ; 
 scalar_t__ ENOMEM ; 
 scalar_t__ ESUCCESS ; 
 int /*<<< orphan*/  FrLdrTempAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FsGetDeviceId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FsSetDeviceSpecific (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IsoLookupFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ OpenReadOnly ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RtlZeroMemory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TAG_ISO_FILE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *) ; 

ARC_STATUS IsoOpen(CHAR* Path, OPENMODE OpenMode, ULONG* FileId)
{
    ISO_FILE_INFO TempFileInfo;
    PISO_FILE_INFO FileHandle;
    ULONG DeviceId;
    ARC_STATUS Status;

    if (OpenMode != OpenReadOnly)
        return EACCES;

    DeviceId = FsGetDeviceId(*FileId);

    TRACE("IsoOpen() FileName = %s\n", Path);

    RtlZeroMemory(&TempFileInfo, sizeof(TempFileInfo));
    Status = IsoLookupFile(Path, DeviceId, &TempFileInfo);
    if (Status != ESUCCESS)
        return ENOENT;

    FileHandle = FrLdrTempAlloc(sizeof(ISO_FILE_INFO), TAG_ISO_FILE);
    if (!FileHandle)
        return ENOMEM;

    RtlCopyMemory(FileHandle, &TempFileInfo, sizeof(ISO_FILE_INFO));

    FsSetDeviceSpecific(*FileId, FileHandle);
    return ESUCCESS;
}