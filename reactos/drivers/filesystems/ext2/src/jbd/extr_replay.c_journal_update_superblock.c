#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct buffer_head {int dummy; } ;
struct TYPE_4__ {scalar_t__ j_tail_sequence; scalar_t__ j_transaction_sequence; scalar_t__ j_tail; scalar_t__ j_errno; int /*<<< orphan*/  j_state_lock; int /*<<< orphan*/  j_flags; struct buffer_head* j_sb_buffer; TYPE_2__* j_superblock; } ;
typedef  TYPE_1__ journal_t ;
struct TYPE_5__ {scalar_t__ s_start; void* s_errno; void* s_sequence; } ;
typedef  TYPE_2__ journal_superblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int /*<<< orphan*/  JFS_FLUSHED ; 
 int /*<<< orphan*/  SWRITE ; 
 void* cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  jbd_debug (int,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  jbd_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ll_rw_block (int /*<<< orphan*/ ,int,struct buffer_head**) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  sync_dirty_buffer (struct buffer_head*) ; 

void journal_update_superblock(journal_t *journal, int wait)
{
    journal_superblock_t *sb = journal->j_superblock;
    struct buffer_head *bh = journal->j_sb_buffer;

    /*
     * As a special case, if the on-disk copy is already marked as needing
     * no recovery (s_start == 0) and there are no outstanding transactions
     * in the filesystem, then we can safely defer the superblock update
     * until the next commit by setting JFS_FLUSHED.  This avoids
     * attempting a write to a potential-readonly device.
     */
    if (sb->s_start == 0 && journal->j_tail_sequence ==
            journal->j_transaction_sequence) {
        jbd_debug(1,"JBD: Skipping superblock update on recovered sb "
                  "(start %ld, seq %d, errno %d)\n",
                  journal->j_tail, journal->j_tail_sequence,
                  journal->j_errno);
        goto out;
    }

    jbd_lock(&journal->j_state_lock);
    jbd_debug(1,"JBD: updating superblock (start %ld, seq %d, errno %d)\n",
              journal->j_tail, journal->j_tail_sequence, journal->j_errno);

    sb->s_sequence = cpu_to_be32(journal->j_tail_sequence);
    sb->s_start    = cpu_to_be32(journal->j_tail);
    sb->s_errno    = cpu_to_be32(journal->j_errno);
    jbd_unlock(&journal->j_state_lock);

    BUFFER_TRACE(bh, "marking dirty");
    mark_buffer_dirty(bh);
    if (wait)
        sync_dirty_buffer(bh);
    else
        ll_rw_block(SWRITE, 1, &bh);

out:
    /* If we have just flushed the log (by marking s_start==0), then
     * any future commit will have to be careful to update the
     * superblock again to re-record the true start of the log. */

    jbd_lock(&journal->j_state_lock);
    if (sb->s_start)
        journal->j_flags &= ~JFS_FLUSHED;
    else
        journal->j_flags |= JFS_FLUSHED;
    jbd_unlock(&journal->j_state_lock);
}