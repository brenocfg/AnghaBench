#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  pbtrfs_file_info ;
struct TYPE_8__ {int /*<<< orphan*/  size; } ;
struct TYPE_6__ {scalar_t__ position; int /*<<< orphan*/  inr; TYPE_4__ inode; } ;
typedef  TYPE_1__ btrfs_file_info ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_7__ {int /*<<< orphan*/  root_dirid; } ;
struct TYPE_9__ {TYPE_3__ FsRoot; } ;
typedef  scalar_t__ OPENMODE ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int /*<<< orphan*/  ARC_STATUS ;

/* Variables and functions */
 scalar_t__ BTRFS_FT_REG_FILE ; 
 TYPE_5__* BtrFsInfo ; 
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EISDIR ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ESUCCESS ; 
 int /*<<< orphan*/  FrLdrTempAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FsSetDeviceSpecific (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INVALID_INODE ; 
 scalar_t__ OpenReadOnly ; 
 int /*<<< orphan*/  TAG_BTRFS_FILE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  btrfs_lookup_path (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

ARC_STATUS BtrFsOpen(CHAR *Path, OPENMODE OpenMode, ULONG *FileId)
{
    u64 inr;
    u8 type;

    btrfs_file_info temp_file_info;
    pbtrfs_file_info phandle;

    TRACE("BtrFsOpen %s\n", Path);

    if (OpenMode != OpenReadOnly)
        return EACCES;

    inr = btrfs_lookup_path(&BtrFsInfo->FsRoot, BtrFsInfo->FsRoot.root_dirid, Path, &type, &temp_file_info.inode, 40);

    if (inr == INVALID_INODE)
    {
        TRACE("Cannot lookup file %s\n", Path);
        return ENOENT;
    }

    if (type != BTRFS_FT_REG_FILE)
    {
        TRACE("Not a regular file: %s\n", Path);
        return EISDIR;
    }

    TRACE("found inode inr=%llu size=%llu\n", inr, temp_file_info.inode.size);

    temp_file_info.inr = inr;
    temp_file_info.position = 0;

    phandle = FrLdrTempAlloc(sizeof(btrfs_file_info), TAG_BTRFS_FILE);
    if (!phandle)
        return ENOMEM;

    memcpy(phandle, &temp_file_info, sizeof(btrfs_file_info));

    FsSetDeviceSpecific(*FileId, phandle);
    return ESUCCESS;
}