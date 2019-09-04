#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct journal_head {TYPE_2__* b_transaction; scalar_t__ b_modified; TYPE_2__* b_next_transaction; } ;
struct buffer_head {int dummy; } ;
struct TYPE_4__ {scalar_t__ t_state; TYPE_1__* t_journal; } ;
struct TYPE_3__ {int /*<<< orphan*/  j_list_lock; } ;

/* Variables and functions */
 int BJ_Forget ; 
 int BJ_Metadata ; 
 int BJ_Reserved ; 
 int /*<<< orphan*/  J_ASSERT_JH (struct journal_head*,int) ; 
 scalar_t__ T_RUNNING ; 
 int /*<<< orphan*/  __jbd2_journal_file_buffer (struct journal_head*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  __jbd2_journal_temp_unlink_buffer (struct journal_head*) ; 
 int /*<<< orphan*/  __jbd2_journal_unfile_buffer (struct journal_head*) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 scalar_t__ buffer_freed (struct buffer_head*) ; 
 int jbd_is_locked_bh_state (struct buffer_head*) ; 
 struct buffer_head* jh2bh (struct journal_head*) ; 
 int /*<<< orphan*/  set_buffer_jbddirty (struct buffer_head*) ; 
 int test_clear_buffer_jbddirty (struct buffer_head*) ; 

void __jbd2_journal_refile_buffer(struct journal_head *jh)
{
	int was_dirty, jlist;
	struct buffer_head *bh = jh2bh(jh);

	J_ASSERT_JH(jh, jbd_is_locked_bh_state(bh));
	if (jh->b_transaction)
		assert_spin_locked(&jh->b_transaction->t_journal->j_list_lock);

	/* If the buffer is now unused, just drop it. */
	if (jh->b_next_transaction == NULL) {
		__jbd2_journal_unfile_buffer(jh);
		return;
	}

	/*
	 * It has been modified by a later transaction: add it to the new
	 * transaction's metadata list.
	 */

	was_dirty = test_clear_buffer_jbddirty(bh);
	__jbd2_journal_temp_unlink_buffer(jh);
	/*
	 * We set b_transaction here because b_next_transaction will inherit
	 * our jh reference and thus __jbd2_journal_file_buffer() must not
	 * take a new one.
	 */
	jh->b_transaction = jh->b_next_transaction;
	jh->b_next_transaction = NULL;
	if (buffer_freed(bh))
		jlist = BJ_Forget;
	else if (jh->b_modified)
		jlist = BJ_Metadata;
	else
		jlist = BJ_Reserved;
	__jbd2_journal_file_buffer(jh, jh->b_transaction, jlist);
	J_ASSERT_JH(jh, jh->b_transaction->t_state == T_RUNNING);

	if (was_dirty)
		set_buffer_jbddirty(bh);
}