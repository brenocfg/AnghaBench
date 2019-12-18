#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  TYPE_2__* pbtrfs_file_info ;
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ ULONG ;
struct TYPE_7__ {int /*<<< orphan*/  FsRoot; } ;
struct TYPE_5__ {scalar_t__ size; } ;
struct TYPE_6__ {int /*<<< orphan*/  position; int /*<<< orphan*/  inr; TYPE_1__ inode; } ;
typedef  int /*<<< orphan*/  ARC_STATUS ;

/* Variables and functions */
 TYPE_4__* BtrFsInfo ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ESUCCESS ; 
 TYPE_2__* FsGetDeviceSpecific (scalar_t__) ; 
 scalar_t__ READ_ERROR ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,...) ; 
 scalar_t__ btrfs_file_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

ARC_STATUS BtrFsRead(ULONG FileId, VOID *Buffer, ULONG Size, ULONG *BytesRead)
{
    pbtrfs_file_info phandle = FsGetDeviceSpecific(FileId);
    u64 rd;

    TRACE("BtrFsRead %lu, size=%lu \n", FileId, Size);

    if (!Size)
        Size = phandle->inode.size;

    if (Size > phandle->inode.size)
        Size = phandle->inode.size;

    rd = btrfs_file_read(&BtrFsInfo->FsRoot, phandle->inr, phandle->position, Size, Buffer);
    if (rd == READ_ERROR)
    {
        TRACE("An error occured while reading file %lu\n", FileId);
        return ENOENT;
    }

    phandle->position += rd;
    *BytesRead = rd;
    return ESUCCESS;
}