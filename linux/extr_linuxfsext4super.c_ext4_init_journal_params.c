#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct ext4_sb_info {int /*<<< orphan*/  s_max_batch_time; int /*<<< orphan*/  s_min_batch_time; int /*<<< orphan*/  s_commit_interval; } ;
struct TYPE_3__ {int /*<<< orphan*/  j_state_lock; int /*<<< orphan*/  j_flags; int /*<<< orphan*/  j_max_batch_time; int /*<<< orphan*/  j_min_batch_time; int /*<<< orphan*/  j_commit_interval; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 int /*<<< orphan*/  BARRIER ; 
 int /*<<< orphan*/  DATA_ERR_ABORT ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  JBD2_ABORT_ON_SYNCDATA_ERR ; 
 int /*<<< orphan*/  JBD2_BARRIER ; 
 scalar_t__ test_opt (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ext4_init_journal_params(struct super_block *sb, journal_t *journal)
{
	struct ext4_sb_info *sbi = EXT4_SB(sb);

	journal->j_commit_interval = sbi->s_commit_interval;
	journal->j_min_batch_time = sbi->s_min_batch_time;
	journal->j_max_batch_time = sbi->s_max_batch_time;

	write_lock(&journal->j_state_lock);
	if (test_opt(sb, BARRIER))
		journal->j_flags |= JBD2_BARRIER;
	else
		journal->j_flags &= ~JBD2_BARRIER;
	if (test_opt(sb, DATA_ERR_ABORT))
		journal->j_flags |= JBD2_ABORT_ON_SYNCDATA_ERR;
	else
		journal->j_flags &= ~JBD2_ABORT_ON_SYNCDATA_ERR;
	write_unlock(&journal->j_state_lock);
}