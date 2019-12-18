#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct super_block {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; struct super_block* i_sb; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {int i_extcnt; int i_ext_last; scalar_t__ i_pa_cnt; scalar_t__ i_lastalloc; scalar_t__ i_protect; scalar_t__ mmu_private; int /*<<< orphan*/ * i_ext_bh; int /*<<< orphan*/ * i_ac; scalar_t__ i_lc_mask; scalar_t__ i_lc_shift; scalar_t__ i_lc_size; int /*<<< orphan*/ * i_lc; scalar_t__ i_blkcnt; int /*<<< orphan*/  i_opencnt; } ;

/* Variables and functions */
 TYPE_1__* AFFS_I (struct inode*) ; 
 int /*<<< orphan*/  affs_alloc_block (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  affs_brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  affs_free_block (struct super_block*,int /*<<< orphan*/ ) ; 
 struct buffer_head* affs_getzeroblk (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  insert_inode_hash (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (struct buffer_head*,struct inode*) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 

struct inode *
affs_new_inode(struct inode *dir)
{
	struct super_block	*sb = dir->i_sb;
	struct inode		*inode;
	u32			 block;
	struct buffer_head	*bh;

	if (!(inode = new_inode(sb)))
		goto err_inode;

	if (!(block = affs_alloc_block(dir, dir->i_ino)))
		goto err_block;

	bh = affs_getzeroblk(sb, block);
	if (!bh)
		goto err_bh;
	mark_buffer_dirty_inode(bh, inode);
	affs_brelse(bh);

	inode->i_uid     = current_fsuid();
	inode->i_gid     = current_fsgid();
	inode->i_ino     = block;
	set_nlink(inode, 1);
	inode->i_mtime   = inode->i_atime = inode->i_ctime = current_time(inode);
	atomic_set(&AFFS_I(inode)->i_opencnt, 0);
	AFFS_I(inode)->i_blkcnt = 0;
	AFFS_I(inode)->i_lc = NULL;
	AFFS_I(inode)->i_lc_size = 0;
	AFFS_I(inode)->i_lc_shift = 0;
	AFFS_I(inode)->i_lc_mask = 0;
	AFFS_I(inode)->i_ac = NULL;
	AFFS_I(inode)->i_ext_bh = NULL;
	AFFS_I(inode)->mmu_private = 0;
	AFFS_I(inode)->i_protect = 0;
	AFFS_I(inode)->i_lastalloc = 0;
	AFFS_I(inode)->i_pa_cnt = 0;
	AFFS_I(inode)->i_extcnt = 1;
	AFFS_I(inode)->i_ext_last = ~1;

	insert_inode_hash(inode);

	return inode;

err_bh:
	affs_free_block(sb, block);
err_block:
	iput(inode);
err_inode:
	return NULL;
}