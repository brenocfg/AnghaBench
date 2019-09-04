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
struct ocfs2_super {struct inode* osb_tl_inode; struct buffer_head* osb_tl_bh; int /*<<< orphan*/  osb_tl_disable; int /*<<< orphan*/  osb_truncate_log_wq; int /*<<< orphan*/  slot_num; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_get_truncate_log_info (struct ocfs2_super*,int /*<<< orphan*/ ,struct inode**,struct buffer_head**) ; 
 int /*<<< orphan*/  ocfs2_truncate_log_worker ; 

int ocfs2_truncate_log_init(struct ocfs2_super *osb)
{
	int status;
	struct inode *tl_inode = NULL;
	struct buffer_head *tl_bh = NULL;

	status = ocfs2_get_truncate_log_info(osb,
					     osb->slot_num,
					     &tl_inode,
					     &tl_bh);
	if (status < 0)
		mlog_errno(status);

	/* ocfs2_truncate_log_shutdown keys on the existence of
	 * osb->osb_tl_inode so we don't set any of the osb variables
	 * until we're sure all is well. */
	INIT_DELAYED_WORK(&osb->osb_truncate_log_wq,
			  ocfs2_truncate_log_worker);
	atomic_set(&osb->osb_tl_disable, 0);
	osb->osb_tl_bh    = tl_bh;
	osb->osb_tl_inode = tl_inode;

	return status;
}