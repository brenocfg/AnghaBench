#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int t_need_data_flush; int /*<<< orphan*/  t_inode_list; int /*<<< orphan*/  t_tid; TYPE_3__* t_journal; } ;
typedef  TYPE_2__ transaction_t ;
struct jbd2_inode {unsigned long i_flags; int /*<<< orphan*/  i_list; TYPE_2__* i_transaction; TYPE_2__* i_next_transaction; void* i_dirty_end; void* i_dirty_start; TYPE_1__* i_vfs_inode; } ;
typedef  void* loff_t ;
struct TYPE_9__ {int /*<<< orphan*/  j_list_lock; TYPE_2__* j_committing_transaction; } ;
typedef  TYPE_3__ journal_t ;
struct TYPE_10__ {TYPE_2__* h_transaction; } ;
typedef  TYPE_4__ handle_t ;
struct TYPE_7__ {int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 int EROFS ; 
 int /*<<< orphan*/  J_ASSERT (int) ; 
 scalar_t__ is_handle_aborted (TYPE_4__*) ; 
 int /*<<< orphan*/  jbd_debug (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* max (void*,void*) ; 
 void* min (void*,void*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int jbd2_journal_file_inode(handle_t *handle, struct jbd2_inode *jinode,
		unsigned long flags, loff_t start_byte, loff_t end_byte)
{
	transaction_t *transaction = handle->h_transaction;
	journal_t *journal;

	if (is_handle_aborted(handle))
		return -EROFS;
	journal = transaction->t_journal;

	jbd_debug(4, "Adding inode %lu, tid:%d\n", jinode->i_vfs_inode->i_ino,
			transaction->t_tid);

	spin_lock(&journal->j_list_lock);
	jinode->i_flags |= flags;

	if (jinode->i_dirty_end) {
		jinode->i_dirty_start = min(jinode->i_dirty_start, start_byte);
		jinode->i_dirty_end = max(jinode->i_dirty_end, end_byte);
	} else {
		jinode->i_dirty_start = start_byte;
		jinode->i_dirty_end = end_byte;
	}

	/* Is inode already attached where we need it? */
	if (jinode->i_transaction == transaction ||
	    jinode->i_next_transaction == transaction)
		goto done;

	/*
	 * We only ever set this variable to 1 so the test is safe. Since
	 * t_need_data_flush is likely to be set, we do the test to save some
	 * cacheline bouncing
	 */
	if (!transaction->t_need_data_flush)
		transaction->t_need_data_flush = 1;
	/* On some different transaction's list - should be
	 * the committing one */
	if (jinode->i_transaction) {
		J_ASSERT(jinode->i_next_transaction == NULL);
		J_ASSERT(jinode->i_transaction ==
					journal->j_committing_transaction);
		jinode->i_next_transaction = transaction;
		goto done;
	}
	/* Not on any transaction list... */
	J_ASSERT(!jinode->i_next_transaction);
	jinode->i_transaction = transaction;
	list_add(&jinode->i_list, &transaction->t_inode_list);
done:
	spin_unlock(&journal->j_list_lock);

	return 0;
}