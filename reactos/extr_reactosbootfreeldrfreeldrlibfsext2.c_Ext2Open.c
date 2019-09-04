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
typedef  int /*<<< orphan*/  PEXT2_FILE_INFO ;
typedef  scalar_t__ OPENMODE ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int /*<<< orphan*/  ARC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ESUCCESS ; 
 int /*<<< orphan*/  Ext2OpenFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FsSetDeviceSpecific (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OpenReadOnly ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *) ; 

ARC_STATUS Ext2Open(CHAR* Path, OPENMODE OpenMode, ULONG* FileId)
{
    PEXT2_FILE_INFO FileHandle;
    //ULONG DeviceId;

    if (OpenMode != OpenReadOnly)
        return EACCES;

    //DeviceId = FsGetDeviceId(*FileId);

    TRACE("Ext2Open() FileName = %s\n", Path);

    //
    // Call old open method
    //
    FileHandle = Ext2OpenFile(Path);

    //
    // Check for error
    //
    if (!FileHandle)
        return ENOENT;

    //
    // Success. Remember the handle
    //
    FsSetDeviceSpecific(*FileId, FileHandle);
    return ESUCCESS;
}