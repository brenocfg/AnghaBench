#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_8__ {scalar_t__ LowPart; scalar_t__ HighPart; } ;
struct TYPE_7__ {scalar_t__ Offset; TYPE_1__* DataContext; } ;
struct TYPE_6__ {int /*<<< orphan*/  Record; } ;
typedef  scalar_t__ SEEKMODE ;
typedef  TYPE_2__* PNTFS_FILE_HANDLE ;
typedef  TYPE_3__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  ARC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ESUCCESS ; 
 TYPE_2__* FsGetDeviceSpecific (scalar_t__) ; 
 scalar_t__ NtfsGetAttributeSize (int /*<<< orphan*/ *) ; 
 scalar_t__ SeekAbsolute ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 

ARC_STATUS NtfsSeek(ULONG FileId, LARGE_INTEGER* Position, SEEKMODE SeekMode)
{
    PNTFS_FILE_HANDLE FileHandle = FsGetDeviceSpecific(FileId);

    TRACE("NtfsSeek() NewFilePointer = %lu\n", Position->LowPart);

    if (SeekMode != SeekAbsolute)
        return EINVAL;
    if (Position->HighPart != 0)
        return EINVAL;
    if (Position->LowPart >= (ULONG)NtfsGetAttributeSize(&FileHandle->DataContext->Record))
        return EINVAL;

    FileHandle->Offset = Position->LowPart;
    return ESUCCESS;
}