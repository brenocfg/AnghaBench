#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tid_t ;
struct TYPE_5__ {unsigned long j_tail; unsigned long j_free; int /*<<< orphan*/  j_state_lock; int /*<<< orphan*/  j_tail_sequence; scalar_t__ j_first; scalar_t__ j_last; int /*<<< orphan*/  j_checkpoint_mutex; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int REQ_FUA ; 
 int REQ_SYNC ; 
 int jbd2_journal_update_sb_log_tail (TYPE_1__*,int /*<<< orphan*/ ,unsigned long,int) ; 
 int /*<<< orphan*/  jbd_debug (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_jbd2_update_log_tail (TYPE_1__*,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

int __jbd2_update_log_tail(journal_t *journal, tid_t tid, unsigned long block)
{
	unsigned long freed;
	int ret;

	BUG_ON(!mutex_is_locked(&journal->j_checkpoint_mutex));

	/*
	 * We cannot afford for write to remain in drive's caches since as
	 * soon as we update j_tail, next transaction can start reusing journal
	 * space and if we lose sb update during power failure we'd replay
	 * old transaction with possibly newly overwritten data.
	 */
	ret = jbd2_journal_update_sb_log_tail(journal, tid, block,
					      REQ_SYNC | REQ_FUA);
	if (ret)
		goto out;

	write_lock(&journal->j_state_lock);
	freed = block - journal->j_tail;
	if (block < journal->j_tail)
		freed += journal->j_last - journal->j_first;

	trace_jbd2_update_log_tail(journal, tid, block, freed);
	jbd_debug(1,
		  "Cleaning journal tail from %u to %u (offset %lu), "
		  "freeing %lu\n",
		  journal->j_tail_sequence, tid, block, freed);

	journal->j_free += freed;
	journal->j_tail_sequence = tid;
	journal->j_tail = block;
	write_unlock(&journal->j_state_lock);

out:
	return ret;
}