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
struct inode {int i_state; int /*<<< orphan*/  i_count; int /*<<< orphan*/  i_lock; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_nlink; } ;

/* Variables and functions */
 scalar_t__ F2FS_HAS_BLOCKS (struct inode*) ; 
 int I_SYNC ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f2fs_destroy_extent_node (struct inode*) ; 
 int /*<<< orphan*/  f2fs_drop_inmem_pages (struct inode*) ; 
 int /*<<< orphan*/  f2fs_i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_is_atomic_file (struct inode*) ; 
 int /*<<< orphan*/  f2fs_truncate (struct inode*) ; 
 int generic_drop_inode (struct inode*) ; 
 int /*<<< orphan*/  inode_unhashed (struct inode*) ; 
 int /*<<< orphan*/  is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  sb_end_intwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_start_intwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_f2fs_drop_inode (struct inode*,int) ; 

__attribute__((used)) static int f2fs_drop_inode(struct inode *inode)
{
	int ret;
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
	trace_f2fs_drop_inode(inode, ret);
	return ret;
}