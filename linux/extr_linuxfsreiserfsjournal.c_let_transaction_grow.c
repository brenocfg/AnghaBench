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
struct reiserfs_journal {unsigned long j_bcount; unsigned int j_trans_id; int /*<<< orphan*/  j_jlock; int /*<<< orphan*/  j_wcount; TYPE_1__* j_current_jl; } ;
struct TYPE_2__ {int /*<<< orphan*/  j_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_COMMIT_PENDING ; 
 struct reiserfs_journal* SB_JOURNAL (struct super_block*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_log_writer (struct super_block*) ; 
 int /*<<< orphan*/  reiserfs_write_lock_nested (struct super_block*,int) ; 
 int reiserfs_write_unlock_nested (struct super_block*) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 

__attribute__((used)) static void let_transaction_grow(struct super_block *sb, unsigned int trans_id)
{
	struct reiserfs_journal *journal = SB_JOURNAL(sb);
	unsigned long bcount = journal->j_bcount;
	while (1) {
		int depth;

		depth = reiserfs_write_unlock_nested(sb);
		schedule_timeout_uninterruptible(1);
		reiserfs_write_lock_nested(sb, depth);

		journal->j_current_jl->j_state |= LIST_COMMIT_PENDING;
		while ((atomic_read(&journal->j_wcount) > 0 ||
			atomic_read(&journal->j_jlock)) &&
		       journal->j_trans_id == trans_id) {
			queue_log_writer(sb);
		}
		if (journal->j_trans_id != trans_id)
			break;
		if (bcount == journal->j_bcount)
			break;
		bcount = journal->j_bcount;
	}
}