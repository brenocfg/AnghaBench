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
struct node_info {scalar_t__ blk_addr; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;
struct f2fs_sb_info {int dummy; } ;

/* Variables and functions */
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  FI_FREE_NID ; 
 scalar_t__ NULL_ADDR ; 
 int /*<<< orphan*/  SBI_NEED_FSCK ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int f2fs_acquire_orphan_inode (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_add_orphan_inode (struct inode*) ; 
 int /*<<< orphan*/  f2fs_alloc_nid_done (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int f2fs_get_node_info (struct f2fs_sb_info*,int /*<<< orphan*/ ,struct node_info*) ; 
 int /*<<< orphan*/  f2fs_inode_synced (struct inode*) ; 
 int /*<<< orphan*/  f2fs_unlock_op (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_update_inode_page (struct inode*) ; 
 int /*<<< orphan*/  f2fs_warn (struct f2fs_sb_info*,char*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sbi_flag (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

void f2fs_handle_failed_inode(struct inode *inode)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	struct node_info ni;
	int err;

	/*
	 * clear nlink of inode in order to release resource of inode
	 * immediately.
	 */
	clear_nlink(inode);

	/*
	 * we must call this to avoid inode being remained as dirty, resulting
	 * in a panic when flushing dirty inodes in gdirty_list.
	 */
	f2fs_update_inode_page(inode);
	f2fs_inode_synced(inode);

	/* don't make bad inode, since it becomes a regular file. */
	unlock_new_inode(inode);

	/*
	 * Note: we should add inode to orphan list before f2fs_unlock_op()
	 * so we can prevent losing this orphan when encoutering checkpoint
	 * and following suddenly power-off.
	 */
	err = f2fs_get_node_info(sbi, inode->i_ino, &ni);
	if (err) {
		set_sbi_flag(sbi, SBI_NEED_FSCK);
		f2fs_warn(sbi, "May loss orphan inode, run fsck to fix.");
		goto out;
	}

	if (ni.blk_addr != NULL_ADDR) {
		err = f2fs_acquire_orphan_inode(sbi);
		if (err) {
			set_sbi_flag(sbi, SBI_NEED_FSCK);
			f2fs_warn(sbi, "Too many orphan inodes, run fsck to fix.");
		} else {
			f2fs_add_orphan_inode(inode);
		}
		f2fs_alloc_nid_done(sbi, inode->i_ino);
	} else {
		set_inode_flag(inode, FI_FREE_NID);
	}

out:
	f2fs_unlock_op(sbi);

	/* iput will drop the inode object */
	iput(inode);
}