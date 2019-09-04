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
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ ULONGLONG ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  PEXT2_FILE_INFO ;
typedef  scalar_t__ BOOLEAN ;
typedef  int /*<<< orphan*/  ARC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ESUCCESS ; 
 scalar_t__ Ext2ReadFileBig (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FsGetDeviceSpecific (scalar_t__) ; 

ARC_STATUS Ext2Read(ULONG FileId, VOID* Buffer, ULONG N, ULONG* Count)
{
    PEXT2_FILE_INFO FileHandle = FsGetDeviceSpecific(FileId);
    ULONGLONG BytesReadBig;
    BOOLEAN Success;

    //
    // Read data
    //
    Success = Ext2ReadFileBig(FileHandle, N, &BytesReadBig, Buffer);
    *Count = (ULONG)BytesReadBig;

    //
    // Check for success
    //
    if (Success)
        return ESUCCESS;
    else
        return EIO;
}