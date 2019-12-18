#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_10__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_11__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_13__ {TYPE_2__ CurrentAddress; TYPE_3__ EndingAddress; } ;
struct TYPE_12__ {int /*<<< orphan*/  Offset; TYPE_1__* DataContext; } ;
struct TYPE_9__ {int /*<<< orphan*/  Record; } ;
typedef  TYPE_4__* PNTFS_FILE_HANDLE ;
typedef  TYPE_5__ FILEINFORMATION ;
typedef  int /*<<< orphan*/  ARC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ESUCCESS ; 
 TYPE_4__* FsGetDeviceSpecific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtfsGetAttributeSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_5__*,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ARC_STATUS NtfsGetFileInformation(ULONG FileId, FILEINFORMATION* Information)
{
    PNTFS_FILE_HANDLE FileHandle = FsGetDeviceSpecific(FileId);

    RtlZeroMemory(Information, sizeof(*Information));
    Information->EndingAddress.QuadPart = NtfsGetAttributeSize(&FileHandle->DataContext->Record);
    Information->CurrentAddress.QuadPart = FileHandle->Offset;

    TRACE("NtfsGetFileInformation(%lu) -> FileSize = %llu, FilePointer = 0x%llx\n",
          FileId, Information->EndingAddress.QuadPart, Information->CurrentAddress.QuadPart);

    return ESUCCESS;
}