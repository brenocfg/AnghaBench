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
typedef  TYPE_2__* pbtrfs_file_info ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_8__ {scalar_t__ QuadPart; } ;
struct TYPE_6__ {scalar_t__ size; } ;
struct TYPE_7__ {scalar_t__ position; TYPE_1__ inode; } ;
typedef  scalar_t__ SEEKMODE ;
typedef  TYPE_3__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  ARC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ESUCCESS ; 
 TYPE_2__* FsGetDeviceSpecific (int /*<<< orphan*/ ) ; 
 scalar_t__ SeekAbsolute ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,scalar_t__) ; 

ARC_STATUS BtrFsSeek(ULONG FileId, LARGE_INTEGER *Position, SEEKMODE SeekMode)
{
    pbtrfs_file_info phandle = FsGetDeviceSpecific(FileId);

    TRACE("BtrFsSeek %lu NewFilePointer = %llu\n", FileId, Position->QuadPart);

    if (SeekMode != SeekAbsolute)
        return EINVAL;
    if (Position->QuadPart >= phandle->inode.size)
        return EINVAL;

    phandle->position = Position->QuadPart;
    return ESUCCESS;
}