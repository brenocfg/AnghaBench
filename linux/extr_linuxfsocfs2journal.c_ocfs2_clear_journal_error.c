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
struct super_block {int /*<<< orphan*/  s_id; } ;
typedef  int /*<<< orphan*/  journal_t ;

/* Variables and functions */
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  jbd2_journal_ack_err (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd2_journal_clear_err (int /*<<< orphan*/ *) ; 
 int jbd2_journal_errno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static void ocfs2_clear_journal_error(struct super_block *sb,
				      journal_t *journal,
				      int slot)
{
	int olderr;

	olderr = jbd2_journal_errno(journal);
	if (olderr) {
		mlog(ML_ERROR, "File system error %d recorded in "
		     "journal %u.\n", olderr, slot);
		mlog(ML_ERROR, "File system on device %s needs checking.\n",
		     sb->s_id);

		jbd2_journal_ack_err(journal);
		jbd2_journal_clear_err(journal);
	}
}