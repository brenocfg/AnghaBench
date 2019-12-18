#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ ULONGLONG ;
typedef  scalar_t__ ULONG ;
struct TYPE_3__ {int /*<<< orphan*/  Offset; int /*<<< orphan*/  DataContext; int /*<<< orphan*/  Volume; } ;
typedef  TYPE_1__* PNTFS_FILE_HANDLE ;
typedef  int /*<<< orphan*/  ARC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ESUCCESS ; 
 TYPE_1__* FsGetDeviceSpecific (scalar_t__) ; 
 scalar_t__ NtfsReadAttribute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

ARC_STATUS NtfsRead(ULONG FileId, VOID* Buffer, ULONG N, ULONG* Count)
{
    PNTFS_FILE_HANDLE FileHandle = FsGetDeviceSpecific(FileId);
    ULONGLONG BytesRead64;

    //
    // Read file
    //
    BytesRead64 = NtfsReadAttribute(FileHandle->Volume, FileHandle->DataContext, FileHandle->Offset, Buffer, N);
    FileHandle->Offset += BytesRead64;
    *Count = (ULONG)BytesRead64;

    //
    // Check for success
    //
    if (BytesRead64 > 0)
        return ESUCCESS;
    else
        return EIO;
}