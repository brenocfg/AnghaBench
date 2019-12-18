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
 int /*<<< orphan*/  dquot_writeback_dquots (struct super_block*,int) ; 
 int /*<<< orphan*/  journal_begin (struct reiserfs_transaction_handle*,struct super_block*,int) ; 
 int /*<<< orphan*/  journal_end_sync (struct reiserfs_transaction_handle*) ; 
 int /*<<< orphan*/  reiserfs_flush_old_commits (struct super_block*) ; 
 int /*<<< orphan*/  reiserfs_write_lock (struct super_block*) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (struct super_block*) ; 

__attribute__((used)) static int reiserfs_sync_fs(struct super_block *s, int wait)
{
	struct reiserfs_transaction_handle th;

	/*
	 * Writeback quota in non-journalled quota case - journalled quota has
	 * no dirty dquots
	 */
	dquot_writeback_dquots(s, -1);
	reiserfs_write_lock(s);
	if (!journal_begin(&th, s, 1))
		if (!journal_end_sync(&th))
			reiserfs_flush_old_commits(s);
	reiserfs_write_unlock(s);
	return 0;
}