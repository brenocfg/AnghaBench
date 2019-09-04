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
struct treepath {int dummy; } ;
struct super_block {int dummy; } ;
struct reiserfs_transaction_handle {int t_refcount; int /*<<< orphan*/  t_trans_id; struct super_block* t_super; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int JOURNAL_PER_BALANCE_CNT ; 
 int journal_begin (struct reiserfs_transaction_handle*,struct super_block*,int) ; 
 int journal_end (struct reiserfs_transaction_handle*) ; 
 int /*<<< orphan*/  pathrelse (struct treepath*) ; 
 int /*<<< orphan*/  reiserfs_update_inode_transaction (struct inode*) ; 
 int /*<<< orphan*/  reiserfs_update_sd (struct reiserfs_transaction_handle*,struct inode*) ; 

__attribute__((used)) static int restart_transaction(struct reiserfs_transaction_handle *th,
			       struct inode *inode, struct treepath *path)
{
	struct super_block *s = th->t_super;
	int err;

	BUG_ON(!th->t_trans_id);
	BUG_ON(!th->t_refcount);

	pathrelse(path);

	/* we cannot restart while nested */
	if (th->t_refcount > 1) {
		return 0;
	}
	reiserfs_update_sd(th, inode);
	err = journal_end(th);
	if (!err) {
		err = journal_begin(th, s, JOURNAL_PER_BALANCE_CNT * 6);
		if (!err)
			reiserfs_update_inode_transaction(inode);
	}
	return err;
}