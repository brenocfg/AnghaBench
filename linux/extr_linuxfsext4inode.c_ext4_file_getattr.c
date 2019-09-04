#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct path {int /*<<< orphan*/  dentry; } ;
struct kstat {int blocks; int size; } ;
struct inode {TYPE_1__* i_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_reserved_data_blocks; } ;
struct TYPE_3__ {int s_blocksize_bits; } ;

/* Variables and functions */
 int EXT4_C2B (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_SB (TYPE_1__*) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_getattr (struct path const*,struct kstat*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ext4_has_inline_data (struct inode*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int ext4_file_getattr(const struct path *path, struct kstat *stat,
		      u32 request_mask, unsigned int query_flags)
{
	struct inode *inode = d_inode(path->dentry);
	u64 delalloc_blocks;

	ext4_getattr(path, stat, request_mask, query_flags);

	/*
	 * If there is inline data in the inode, the inode will normally not
	 * have data blocks allocated (it may have an external xattr block).
	 * Report at least one sector for such files, so tools like tar, rsync,
	 * others don't incorrectly think the file is completely sparse.
	 */
	if (unlikely(ext4_has_inline_data(inode)))
		stat->blocks += (stat->size + 511) >> 9;

	/*
	 * We can't update i_blocks if the block allocation is delayed
	 * otherwise in the case of system crash before the real block
	 * allocation is done, we will have i_blocks inconsistent with
	 * on-disk file blocks.
	 * We always keep i_blocks updated together with real
	 * allocation. But to not confuse with user, stat
	 * will return the blocks that include the delayed allocation
	 * blocks for this file.
	 */
	delalloc_blocks = EXT4_C2B(EXT4_SB(inode->i_sb),
				   EXT4_I(inode)->i_reserved_data_blocks);
	stat->blocks += delalloc_blocks << (inode->i_sb->s_blocksize_bits - 9);
	return 0;
}