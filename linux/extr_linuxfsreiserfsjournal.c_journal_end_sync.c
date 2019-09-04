#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct super_block {int dummy; } ;
struct reiserfs_transaction_handle {int t_refcount; int /*<<< orphan*/  t_trans_id; struct super_block* t_super; } ;
struct reiserfs_journal {scalar_t__ j_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int COMMIT_NOW ; 
 int /*<<< orphan*/  SB_BUFFER_WITH_SB (struct super_block*) ; 
 struct reiserfs_journal* SB_JOURNAL (struct super_block*) ; 
 int WAIT ; 
 int do_journal_end (struct reiserfs_transaction_handle*,int) ; 
 int /*<<< orphan*/  journal_mark_dirty (struct reiserfs_transaction_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_prepare_for_journal (struct super_block*,int /*<<< orphan*/ ,int) ; 

int journal_end_sync(struct reiserfs_transaction_handle *th)
{
	struct super_block *sb = th->t_super;
	struct reiserfs_journal *journal = SB_JOURNAL(sb);

	BUG_ON(!th->t_trans_id);
	/* you can sync while nested, very, very bad */
	BUG_ON(th->t_refcount > 1);
	if (journal->j_len == 0) {
		reiserfs_prepare_for_journal(sb, SB_BUFFER_WITH_SB(sb),
					     1);
		journal_mark_dirty(th, SB_BUFFER_WITH_SB(sb));
	}
	return do_journal_end(th, COMMIT_NOW | WAIT);
}