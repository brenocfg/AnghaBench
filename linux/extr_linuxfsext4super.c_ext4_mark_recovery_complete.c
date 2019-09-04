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
struct ext4_super_block {int dummy; } ;
typedef  int /*<<< orphan*/  journal_t ;
struct TYPE_2__ {int /*<<< orphan*/ * s_journal; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 TYPE_1__* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  ext4_clear_feature_journal_needs_recovery (struct super_block*) ; 
 int /*<<< orphan*/  ext4_commit_super (struct super_block*,int) ; 
 int /*<<< orphan*/  ext4_has_feature_journal (struct super_block*) ; 
 scalar_t__ ext4_has_feature_journal_needs_recovery (struct super_block*) ; 
 scalar_t__ jbd2_journal_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd2_journal_lock_updates (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd2_journal_unlock_updates (int /*<<< orphan*/ *) ; 
 scalar_t__ sb_rdonly (struct super_block*) ; 

__attribute__((used)) static void ext4_mark_recovery_complete(struct super_block *sb,
					struct ext4_super_block *es)
{
	journal_t *journal = EXT4_SB(sb)->s_journal;

	if (!ext4_has_feature_journal(sb)) {
		BUG_ON(journal != NULL);
		return;
	}
	jbd2_journal_lock_updates(journal);
	if (jbd2_journal_flush(journal) < 0)
		goto out;

	if (ext4_has_feature_journal_needs_recovery(sb) && sb_rdonly(sb)) {
		ext4_clear_feature_journal_needs_recovery(sb);
		ext4_commit_super(sb, 1);
	}

out:
	jbd2_journal_unlock_updates(journal);
}