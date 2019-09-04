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
typedef  scalar_t__ u64 ;
struct ufs_sb_private_info {int s_bshift; int s_apb; int /*<<< orphan*/  s_bsize; } ;
struct ufs_inode_info {int /*<<< orphan*/  truncate_mutex; int /*<<< orphan*/  meta_lock; int /*<<< orphan*/  i_lastfrag; } ;
struct ufs_buffer_head {int dummy; } ;
struct super_block {int dummy; } ;
struct inode {int i_size; struct super_block* i_sb; } ;
typedef  int sector_t ;
struct TYPE_2__ {struct ufs_sb_private_info* s_uspi; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIRECT_FRAGMENT ; 
 struct ufs_inode_info* UFS_I (struct inode*) ; 
 unsigned int UFS_IND_BLOCK ; 
 TYPE_1__* UFS_SB (struct super_block*) ; 
 unsigned int UFS_TIND_BLOCK ; 
 int /*<<< orphan*/  free_branch_tail (struct inode*,unsigned int,struct ufs_buffer_head*,int) ; 
 int /*<<< orphan*/  free_full_branch (struct inode*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_seqlock_excl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_sequnlock_excl (int /*<<< orphan*/ *) ; 
 struct ufs_buffer_head* ubh_bread (struct super_block*,scalar_t__,int /*<<< orphan*/ ) ; 
 void* ubh_get_data_ptr (struct ufs_sb_private_info*,struct ufs_buffer_head*,int /*<<< orphan*/ ) ; 
 int ufs_block_to_path (struct inode*,int,unsigned int*) ; 
 int /*<<< orphan*/  ufs_data_ptr_clear (struct ufs_sb_private_info*,void*) ; 
 scalar_t__ ufs_data_ptr_to_cpu (struct super_block*,void*) ; 
 void* ufs_get_direct_data_ptr (struct ufs_sb_private_info*,struct ufs_inode_info*,unsigned int) ; 
 int /*<<< orphan*/  ufs_trunc_direct (struct inode*) ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ufs_truncate_blocks(struct inode *inode)
{
	struct ufs_inode_info *ufsi = UFS_I(inode);
	struct super_block *sb = inode->i_sb;
	struct ufs_sb_private_info *uspi = UFS_SB(sb)->s_uspi;
	unsigned offsets[4];
	int depth;
	int depth2;
	unsigned i;
	struct ufs_buffer_head *ubh[3];
	void *p;
	u64 block;

	if (inode->i_size) {
		sector_t last = (inode->i_size - 1) >> uspi->s_bshift;
		depth = ufs_block_to_path(inode, last, offsets);
		if (!depth)
			return;
	} else {
		depth = 1;
	}

	for (depth2 = depth - 1; depth2; depth2--)
		if (offsets[depth2] != uspi->s_apb - 1)
			break;

	mutex_lock(&ufsi->truncate_mutex);
	if (depth == 1) {
		ufs_trunc_direct(inode);
		offsets[0] = UFS_IND_BLOCK;
	} else {
		/* get the blocks that should be partially emptied */
		p = ufs_get_direct_data_ptr(uspi, ufsi, offsets[0]++);
		for (i = 0; i < depth2; i++) {
			block = ufs_data_ptr_to_cpu(sb, p);
			if (!block)
				break;
			ubh[i] = ubh_bread(sb, block, uspi->s_bsize);
			if (!ubh[i]) {
				write_seqlock(&ufsi->meta_lock);
				ufs_data_ptr_clear(uspi, p);
				write_sequnlock(&ufsi->meta_lock);
				break;
			}
			p = ubh_get_data_ptr(uspi, ubh[i], offsets[i + 1]++);
		}
		while (i--)
			free_branch_tail(inode, offsets[i + 1], ubh[i], depth - i - 1);
	}
	for (i = offsets[0]; i <= UFS_TIND_BLOCK; i++) {
		p = ufs_get_direct_data_ptr(uspi, ufsi, i);
		block = ufs_data_ptr_to_cpu(sb, p);
		if (block) {
			write_seqlock(&ufsi->meta_lock);
			ufs_data_ptr_clear(uspi, p);
			write_sequnlock(&ufsi->meta_lock);
			free_full_branch(inode, block, i - UFS_IND_BLOCK + 1);
		}
	}
	read_seqlock_excl(&ufsi->meta_lock);
	ufsi->i_lastfrag = DIRECT_FRAGMENT;
	read_sequnlock_excl(&ufsi->meta_lock);
	mark_inode_dirty(inode);
	mutex_unlock(&ufsi->truncate_mutex);
}