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
struct jfs_inode_info {scalar_t__ fileset; int active_ag; int /*<<< orphan*/  ag_lock; int /*<<< orphan*/  anon_inode_list; } ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_data; int /*<<< orphan*/  i_nlink; } ;
struct bmap {int /*<<< orphan*/ * db_active; } ;
struct TYPE_2__ {struct bmap* bmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  COMMIT_Freewmap ; 
 scalar_t__ FILESYSTEM_I ; 
 struct jfs_inode_info* JFS_IP (struct inode*) ; 
 TYPE_1__* JFS_SBI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  diFree (struct inode*) ; 
 int /*<<< orphan*/  dquot_drop (struct inode*) ; 
 int /*<<< orphan*/  dquot_free_inode (struct inode*) ; 
 int /*<<< orphan*/  dquot_initialize (struct inode*) ; 
 int /*<<< orphan*/  is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  jfs_free_zero_link (struct inode*) ; 
 int /*<<< orphan*/  jfs_info (char*,struct inode*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_cflag (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  truncate_inode_pages_final (int /*<<< orphan*/ *) ; 

void jfs_evict_inode(struct inode *inode)
{
	struct jfs_inode_info *ji = JFS_IP(inode);

	jfs_info("In jfs_evict_inode, inode = 0x%p", inode);

	if (!inode->i_nlink && !is_bad_inode(inode)) {
		dquot_initialize(inode);

		if (JFS_IP(inode)->fileset == FILESYSTEM_I) {
			truncate_inode_pages_final(&inode->i_data);

			if (test_cflag(COMMIT_Freewmap, inode))
				jfs_free_zero_link(inode);

			diFree(inode);

			/*
			 * Free the inode from the quota allocation.
			 */
			dquot_free_inode(inode);
		}
	} else {
		truncate_inode_pages_final(&inode->i_data);
	}
	clear_inode(inode);
	dquot_drop(inode);

	BUG_ON(!list_empty(&ji->anon_inode_list));

	spin_lock_irq(&ji->ag_lock);
	if (ji->active_ag != -1) {
		struct bmap *bmap = JFS_SBI(inode->i_sb)->bmap;
		atomic_dec(&bmap->db_active[ji->active_ag]);
		ji->active_ag = -1;
	}
	spin_unlock_irq(&ji->ag_lock);
}