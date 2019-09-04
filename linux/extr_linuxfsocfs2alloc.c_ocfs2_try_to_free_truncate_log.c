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
struct ocfs2_super {unsigned int truncated_clusters; TYPE_1__* journal; int /*<<< orphan*/  osb_tl_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  j_journal; } ;

/* Variables and functions */
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ jbd2_journal_start_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd2_log_wait_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_flush_truncate_log (struct ocfs2_super*) ; 

int ocfs2_try_to_free_truncate_log(struct ocfs2_super *osb,
					unsigned int needed)
{
	tid_t target;
	int ret = 0;
	unsigned int truncated_clusters;

	inode_lock(osb->osb_tl_inode);
	truncated_clusters = osb->truncated_clusters;
	inode_unlock(osb->osb_tl_inode);

	/*
	 * Check whether we can succeed in allocating if we free
	 * the truncate log.
	 */
	if (truncated_clusters < needed)
		goto out;

	ret = ocfs2_flush_truncate_log(osb);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	if (jbd2_journal_start_commit(osb->journal->j_journal, &target)) {
		jbd2_log_wait_commit(osb->journal->j_journal, target);
		ret = 1;
	}
out:
	return ret;
}