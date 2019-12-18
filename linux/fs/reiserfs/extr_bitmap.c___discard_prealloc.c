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
struct reiserfs_transaction_handle {int /*<<< orphan*/  t_super; int /*<<< orphan*/  t_trans_id; } ;
struct inode {int dummy; } ;
struct reiserfs_inode_info {unsigned long i_prealloc_block; scalar_t__ i_prealloc_count; int /*<<< orphan*/  i_prealloc_list; struct inode vfs_inode; } ;
typedef  int /*<<< orphan*/  b_blocknr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reiserfs_error (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  reiserfs_free_prealloc_block (struct reiserfs_transaction_handle*,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_update_sd (struct reiserfs_transaction_handle*,struct inode*) ; 

__attribute__((used)) static void __discard_prealloc(struct reiserfs_transaction_handle *th,
			       struct reiserfs_inode_info *ei)
{
	unsigned long save = ei->i_prealloc_block;
	int dirty = 0;
	struct inode *inode = &ei->vfs_inode;

	BUG_ON(!th->t_trans_id);
#ifdef CONFIG_REISERFS_CHECK
	if (ei->i_prealloc_count < 0)
		reiserfs_error(th->t_super, "zam-4001",
			       "inode has negative prealloc blocks count.");
#endif
	while (ei->i_prealloc_count > 0) {
		b_blocknr_t block_to_free;

		/*
		 * reiserfs_free_prealloc_block can drop the write lock,
		 * which could allow another caller to free the same block.
		 * We can protect against it by modifying the prealloc
		 * state before calling it.
		 */
		block_to_free = ei->i_prealloc_block++;
		ei->i_prealloc_count--;
		reiserfs_free_prealloc_block(th, inode, block_to_free);
		dirty = 1;
	}
	if (dirty)
		reiserfs_update_sd(th, inode);
	ei->i_prealloc_block = save;
	list_del_init(&ei->i_prealloc_list);
}