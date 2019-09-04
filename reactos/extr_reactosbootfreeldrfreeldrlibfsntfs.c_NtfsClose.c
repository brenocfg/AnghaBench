#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_4__ {int /*<<< orphan*/  DataContext; } ;
typedef  TYPE_1__* PNTFS_FILE_HANDLE ;
typedef  int /*<<< orphan*/  ARC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ESUCCESS ; 
 int /*<<< orphan*/  FrLdrTempFree (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* FsGetDeviceSpecific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtfsReleaseAttributeContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG_NTFS_FILE ; 

ARC_STATUS NtfsClose(ULONG FileId)
{
    PNTFS_FILE_HANDLE FileHandle = FsGetDeviceSpecific(FileId);

    NtfsReleaseAttributeContext(FileHandle->DataContext);
    FrLdrTempFree(FileHandle, TAG_NTFS_FILE);

    return ESUCCESS;
}