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
struct TYPE_5__ {int /*<<< orphan*/  j_state_lock; int /*<<< orphan*/  j_flags; int /*<<< orphan*/  j_tail_sequence; int /*<<< orphan*/  j_sb_buffer; int /*<<< orphan*/  j_checkpoint_mutex; TYPE_2__* j_superblock; } ;
typedef  TYPE_1__ journal_t ;
struct TYPE_6__ {scalar_t__ s_start; void* s_sequence; } ;
typedef  TYPE_2__ journal_superblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  JBD2_FLUSHED ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd2_write_superblock (TYPE_1__*,int) ; 
 int /*<<< orphan*/  jbd_debug (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void jbd2_mark_journal_empty(journal_t *journal, int write_op)
{
	journal_superblock_t *sb = journal->j_superblock;

	BUG_ON(!mutex_is_locked(&journal->j_checkpoint_mutex));
	lock_buffer(journal->j_sb_buffer);
	if (sb->s_start == 0) {		/* Is it already empty? */
		unlock_buffer(journal->j_sb_buffer);
		return;
	}

	jbd_debug(1, "JBD2: Marking journal as empty (seq %u)\n",
		  journal->j_tail_sequence);

	sb->s_sequence = cpu_to_be32(journal->j_tail_sequence);
	sb->s_start    = cpu_to_be32(0);

	jbd2_write_superblock(journal, write_op);

	/* Log is no longer empty */
	write_lock(&journal->j_state_lock);
	journal->j_flags |= JBD2_FLUSHED;
	write_unlock(&journal->j_state_lock);
}