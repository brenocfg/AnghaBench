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
struct ocfs2_super {struct inode* osb_tl_inode; int /*<<< orphan*/  osb_tl_bh; int /*<<< orphan*/  ocfs2_wq; int /*<<< orphan*/  osb_truncate_log_wq; int /*<<< orphan*/  osb_tl_disable; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_flush_truncate_log (struct ocfs2_super*) ; 

void ocfs2_truncate_log_shutdown(struct ocfs2_super *osb)
{
	int status;
	struct inode *tl_inode = osb->osb_tl_inode;

	atomic_set(&osb->osb_tl_disable, 1);

	if (tl_inode) {
		cancel_delayed_work(&osb->osb_truncate_log_wq);
		flush_workqueue(osb->ocfs2_wq);

		status = ocfs2_flush_truncate_log(osb);
		if (status < 0)
			mlog_errno(status);

		brelse(osb->osb_tl_bh);
		iput(osb->osb_tl_inode);
	}
}