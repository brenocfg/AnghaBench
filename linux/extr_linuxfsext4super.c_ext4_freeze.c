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
typedef  int /*<<< orphan*/  journal_t ;
struct TYPE_2__ {int /*<<< orphan*/ * s_journal; } ;

/* Variables and functions */
 TYPE_1__* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  ext4_clear_feature_journal_needs_recovery (struct super_block*) ; 
 int ext4_commit_super (struct super_block*,int) ; 
 int jbd2_journal_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd2_journal_lock_updates (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd2_journal_unlock_updates (int /*<<< orphan*/ *) ; 
 scalar_t__ sb_rdonly (struct super_block*) ; 

__attribute__((used)) static int ext4_freeze(struct super_block *sb)
{
	int error = 0;
	journal_t *journal;

	if (sb_rdonly(sb))
		return 0;

	journal = EXT4_SB(sb)->s_journal;

	if (journal) {
		/* Now we set up the journal barrier. */
		jbd2_journal_lock_updates(journal);

		/*
		 * Don't clear the needs_recovery flag if we failed to
		 * flush the journal.
		 */
		error = jbd2_journal_flush(journal);
		if (error < 0)
			goto out;

		/* Journal blocked and flushed, clear needs_recovery flag. */
		ext4_clear_feature_journal_needs_recovery(sb);
	}

	error = ext4_commit_super(sb, 1);
out:
	if (journal)
		/* we rely on upper layer to stop further updates */
		jbd2_journal_unlock_updates(journal);
	return error;
}