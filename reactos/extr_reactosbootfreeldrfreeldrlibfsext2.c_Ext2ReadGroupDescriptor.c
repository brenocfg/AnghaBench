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
typedef  size_t ULONG ;
struct TYPE_4__ {int /*<<< orphan*/  used_dirs; int /*<<< orphan*/  free_inodes; int /*<<< orphan*/  free_blocks; int /*<<< orphan*/  inode_table_id; int /*<<< orphan*/  inode_id; int /*<<< orphan*/  block_id; } ;
typedef  TYPE_1__* PEXT2_GROUP_DESC ;
typedef  int /*<<< orphan*/  EXT2_GROUP_DESC ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/ * Ext2GroupDescriptors ; 
 int /*<<< orphan*/  RtlCopyMemory (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN Ext2ReadGroupDescriptor(ULONG Group, PEXT2_GROUP_DESC GroupBuffer)
{
    TRACE("Ext2ReadGroupDescriptor()\n");

    /*if (!Ext2ReadBlock(Ext2GetGroupDescBlockNumber(Group), (PVOID)FILESYSBUFFER))
    {
        return FALSE;
    }

    RtlCopyMemory(GroupBuffer, (PVOID)(FILESYSBUFFER + Ext2GetGroupDescOffsetInBlock(Group)), sizeof(EXT2_GROUP_DESC));*/

    RtlCopyMemory(GroupBuffer, &Ext2GroupDescriptors[Group], sizeof(EXT2_GROUP_DESC));

    TRACE("Dumping group descriptor:\n");
    TRACE("block_id = %d\n", GroupBuffer->block_id);
    TRACE("inode_id = %d\n", GroupBuffer->inode_id);
    TRACE("inode_table_id = %d\n", GroupBuffer->inode_table_id);
    TRACE("free_blocks = %d\n", GroupBuffer->free_blocks);
    TRACE("free_inodes = %d\n", GroupBuffer->free_inodes);
    TRACE("used_dirs = %d\n", GroupBuffer->used_dirs);

    return TRUE;
}