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
struct reiserfs_transaction_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SB_BUFFER_WITH_SB (struct super_block*) ; 
 int journal_begin (struct reiserfs_transaction_handle*,struct super_block*,int) ; 
 int /*<<< orphan*/  journal_end_sync (struct reiserfs_transaction_handle*) ; 
 int /*<<< orphan*/  journal_mark_dirty (struct reiserfs_transaction_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_block_writes (struct reiserfs_transaction_handle*) ; 
 int /*<<< orphan*/  reiserfs_cancel_old_flush (struct super_block*) ; 
 int /*<<< orphan*/  reiserfs_prepare_for_journal (struct super_block*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reiserfs_write_lock (struct super_block*) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (struct super_block*) ; 
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 

__attribute__((used)) static int reiserfs_freeze(struct super_block *s)
{
	struct reiserfs_transaction_handle th;

	reiserfs_cancel_old_flush(s);

	reiserfs_write_lock(s);
	if (!sb_rdonly(s)) {
		int err = journal_begin(&th, s, 1);
		if (err) {
			reiserfs_block_writes(&th);
		} else {
			reiserfs_prepare_for_journal(s, SB_BUFFER_WITH_SB(s),
						     1);
			journal_mark_dirty(&th, SB_BUFFER_WITH_SB(s));
			reiserfs_block_writes(&th);
			journal_end_sync(&th);
		}
	}
	reiserfs_write_unlock(s);
	return 0;
}