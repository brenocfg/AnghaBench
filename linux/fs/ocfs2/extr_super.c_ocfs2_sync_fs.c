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
typedef  int /*<<< orphan*/  tid_t ;
struct super_block {int dummy; } ;
struct ocfs2_super {TYPE_1__* journal; } ;
struct TYPE_2__ {int /*<<< orphan*/  j_journal; } ;

/* Variables and functions */
 int EROFS ; 
 struct ocfs2_super* OCFS2_SB (struct super_block*) ; 
 scalar_t__ jbd2_journal_start_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd2_log_wait_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_flush_truncate_log (struct ocfs2_super*) ; 
 scalar_t__ ocfs2_is_hard_readonly (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_schedule_truncate_log_flush (struct ocfs2_super*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_sync_fs(struct super_block *sb, int wait)
{
	int status;
	tid_t target;
	struct ocfs2_super *osb = OCFS2_SB(sb);

	if (ocfs2_is_hard_readonly(osb))
		return -EROFS;

	if (wait) {
		status = ocfs2_flush_truncate_log(osb);
		if (status < 0)
			mlog_errno(status);
	} else {
		ocfs2_schedule_truncate_log_flush(osb, 0);
	}

	if (jbd2_journal_start_commit(osb->journal->j_journal,
				      &target)) {
		if (wait)
			jbd2_log_wait_commit(osb->journal->j_journal,
					     target);
	}
	return 0;
}