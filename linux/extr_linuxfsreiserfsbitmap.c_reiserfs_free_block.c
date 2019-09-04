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
struct super_block {int dummy; } ;
struct reiserfs_transaction_handle {struct super_block* t_super; int /*<<< orphan*/  t_trans_id; } ;
struct inode {int dummy; } ;
typedef  scalar_t__ b_blocknr_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_rs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_1__* REISERFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  RFALSE (int,char*) ; 
 int /*<<< orphan*/  _reiserfs_free_block (struct reiserfs_transaction_handle*,struct inode*,scalar_t__,int) ; 
 int /*<<< orphan*/  is_reusable (struct super_block*,scalar_t__,int) ; 
 int /*<<< orphan*/  journal_mark_freed (struct reiserfs_transaction_handle*,struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  reiserfs_error (struct super_block*,char*,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ sb_block_count (int /*<<< orphan*/ ) ; 

void reiserfs_free_block(struct reiserfs_transaction_handle *th,
			 struct inode *inode, b_blocknr_t block,
			 int for_unformatted)
{
	struct super_block *s = th->t_super;

	BUG_ON(!th->t_trans_id);
	RFALSE(!s, "vs-4061: trying to free block on nonexistent device");
	if (!is_reusable(s, block, 1))
		return;

	if (block > sb_block_count(REISERFS_SB(s)->s_rs)) {
		reiserfs_error(th->t_super, "bitmap-4072",
			       "Trying to free block outside file system "
			       "boundaries (%lu > %lu)",
			       block, sb_block_count(REISERFS_SB(s)->s_rs));
		return;
	}
	/* mark it before we clear it, just in case */
	journal_mark_freed(th, s, block);
	_reiserfs_free_block(th, inode, block, for_unformatted);
}