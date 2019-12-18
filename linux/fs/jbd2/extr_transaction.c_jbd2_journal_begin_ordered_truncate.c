#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  transaction_t ;
struct jbd2_inode {TYPE_1__* i_vfs_inode; int /*<<< orphan*/ * i_transaction; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_6__ {int /*<<< orphan*/  j_list_lock; int /*<<< orphan*/  j_state_lock; int /*<<< orphan*/ * j_committing_transaction; } ;
typedef  TYPE_2__ journal_t ;
struct TYPE_5__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLONG_MAX ; 
 int filemap_fdatawrite_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd2_journal_abort (TYPE_2__*,int) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int jbd2_journal_begin_ordered_truncate(journal_t *journal,
					struct jbd2_inode *jinode,
					loff_t new_size)
{
	transaction_t *inode_trans, *commit_trans;
	int ret = 0;

	/* This is a quick check to avoid locking if not necessary */
	if (!jinode->i_transaction)
		goto out;
	/* Locks are here just to force reading of recent values, it is
	 * enough that the transaction was not committing before we started
	 * a transaction adding the inode to orphan list */
	read_lock(&journal->j_state_lock);
	commit_trans = journal->j_committing_transaction;
	read_unlock(&journal->j_state_lock);
	spin_lock(&journal->j_list_lock);
	inode_trans = jinode->i_transaction;
	spin_unlock(&journal->j_list_lock);
	if (inode_trans == commit_trans) {
		ret = filemap_fdatawrite_range(jinode->i_vfs_inode->i_mapping,
			new_size, LLONG_MAX);
		if (ret)
			jbd2_journal_abort(journal, ret);
	}
out:
	return ret;
}