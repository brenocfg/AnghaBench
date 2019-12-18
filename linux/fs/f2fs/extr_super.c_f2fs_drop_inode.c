#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct inode {scalar_t__ i_ino; int i_state; int /*<<< orphan*/  i_count; int /*<<< orphan*/  i_lock; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_nlink; } ;
struct f2fs_sb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 scalar_t__ F2FS_HAS_BLOCKS (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 scalar_t__ F2FS_META_INO (struct f2fs_sb_info*) ; 
 scalar_t__ F2FS_NODE_INO (struct f2fs_sb_info*) ; 
 int I_SYNC ; 
 int /*<<< orphan*/  SBI_CP_DISABLED ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f2fs_destroy_extent_node (struct inode*) ; 
 int /*<<< orphan*/  f2fs_drop_inmem_pages (struct inode*) ; 
 int /*<<< orphan*/  f2fs_i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_is_atomic_file (struct inode*) ; 
 int /*<<< orphan*/  f2fs_submit_merged_write_cond (struct f2fs_sb_info*,struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_truncate (struct inode*) ; 
 int fscrypt_drop_inode (struct inode*) ; 
 int generic_drop_inode (struct inode*) ; 
 int /*<<< orphan*/  inode_unhashed (struct inode*) ; 
 int /*<<< orphan*/  is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_end_intwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_start_intwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_f2fs_drop_inode (struct inode*,int) ; 
 int /*<<< orphan*/  truncate_inode_pages_final (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f2fs_drop_inode(struct inode *inode)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	int ret;

	/*
	 * during filesystem shutdown, if checkpoint is disabled,
	 * drop useless meta/node dirty pages.
	 */
	if (unlikely(is_sbi_flag_set(sbi, SBI_CP_DISABLED))) {
		if (inode->i_ino == F2FS_NODE_INO(sbi) ||
			inode->i_ino == F2FS_META_INO(sbi)) {
			trace_f2fs_drop_inode(inode, 1);
			return 1;
		}
	}

	/*
	 * This is to avoid a deadlock condition like below.
	 * writeback_single_inode(inode)
	 *  - f2fs_write_data_page
	 *    - f2fs_gc -> iput -> evict
	 *       - inode_wait_for_writeback(inode)
	 */
	if ((!inode_unhashed(inode) && inode->i_state & I_SYNC)) {
		if (!inode->i_nlink && !is_bad_inode(inode)) {
			/* to avoid evict_inode call simultaneously */
			atomic_inc(&inode->i_count);
			spin_unlock(&inode->i_lock);

			/* some remained atomic pages should discarded */
			if (f2fs_is_atomic_file(inode))
				f2fs_drop_inmem_pages(inode);

			/* should remain fi->extent_tree for writepage */
			f2fs_destroy_extent_node(inode);

			sb_start_intwrite(inode->i_sb);
			f2fs_i_size_write(inode, 0);

			f2fs_submit_merged_write_cond(F2FS_I_SB(inode),
					inode, NULL, 0, DATA);
			truncate_inode_pages_final(inode->i_mapping);

			if (F2FS_HAS_BLOCKS(inode))
				f2fs_truncate(inode);

			sb_end_intwrite(inode->i_sb);

			spin_lock(&inode->i_lock);
			atomic_dec(&inode->i_count);
		}
		trace_f2fs_drop_inode(inode, 0);
		return 0;
	}
	ret = generic_drop_inode(inode);
	if (!ret)
		ret = fscrypt_drop_inode(inode);
	trace_f2fs_drop_inode(inode, ret);
	return ret;
}