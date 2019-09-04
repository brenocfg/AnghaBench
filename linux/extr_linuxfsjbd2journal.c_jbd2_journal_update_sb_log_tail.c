#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long tid_t ;
struct TYPE_6__ {int /*<<< orphan*/  j_state_lock; int /*<<< orphan*/  j_flags; int /*<<< orphan*/  j_sb_buffer; int /*<<< orphan*/  j_checkpoint_mutex; TYPE_2__* j_superblock; } ;
typedef  TYPE_1__ journal_t ;
struct TYPE_7__ {void* s_sequence; void* s_start; } ;
typedef  TYPE_2__ journal_superblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int /*<<< orphan*/  JBD2_FLUSHED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 void* cpu_to_be32 (unsigned long) ; 
 scalar_t__ is_journal_aborted (TYPE_1__*) ; 
 int jbd2_write_superblock (TYPE_1__*,int) ; 
 int /*<<< orphan*/  jbd_debug (int,char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  lock_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

int jbd2_journal_update_sb_log_tail(journal_t *journal, tid_t tail_tid,
				     unsigned long tail_block, int write_op)
{
	journal_superblock_t *sb = journal->j_superblock;
	int ret;

	if (is_journal_aborted(journal))
		return -EIO;

	BUG_ON(!mutex_is_locked(&journal->j_checkpoint_mutex));
	jbd_debug(1, "JBD2: updating superblock (start %lu, seq %u)\n",
		  tail_block, tail_tid);

	lock_buffer(journal->j_sb_buffer);
	sb->s_sequence = cpu_to_be32(tail_tid);
	sb->s_start    = cpu_to_be32(tail_block);

	ret = jbd2_write_superblock(journal, write_op);
	if (ret)
		goto out;

	/* Log is no longer empty */
	write_lock(&journal->j_state_lock);
	WARN_ON(!sb->s_sequence);
	journal->j_flags &= ~JBD2_FLUSHED;
	write_unlock(&journal->j_state_lock);

out:
	return ret;
}