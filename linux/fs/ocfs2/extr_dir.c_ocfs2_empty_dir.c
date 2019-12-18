#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  actor; } ;
struct ocfs2_empty_dir_priv {int /*<<< orphan*/  seen_other; int /*<<< orphan*/  seen_dot_dot; int /*<<< orphan*/  seen_dot; TYPE_1__ ctx; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {scalar_t__ ip_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  ML_ERROR ; 
 TYPE_2__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_dir_foreach (struct inode*,TYPE_1__*) ; 
 scalar_t__ ocfs2_dir_indexed (struct inode*) ; 
 int ocfs2_empty_dir_dx (struct inode*,struct ocfs2_empty_dir_priv*) ; 
 int /*<<< orphan*/  ocfs2_empty_dir_filldir ; 

int ocfs2_empty_dir(struct inode *inode)
{
	int ret;
	struct ocfs2_empty_dir_priv priv = {
		.ctx.actor = ocfs2_empty_dir_filldir,
	};

	if (ocfs2_dir_indexed(inode)) {
		ret = ocfs2_empty_dir_dx(inode, &priv);
		if (ret)
			mlog_errno(ret);
		/*
		 * We still run ocfs2_dir_foreach to get the checks
		 * for "." and "..".
		 */
	}

	ret = ocfs2_dir_foreach(inode, &priv.ctx);
	if (ret)
		mlog_errno(ret);

	if (!priv.seen_dot || !priv.seen_dot_dot) {
		mlog(ML_ERROR, "bad directory (dir #%llu) - no `.' or `..'\n",
		     (unsigned long long)OCFS2_I(inode)->ip_blkno);
		/*
		 * XXX: Is it really safe to allow an unlink to continue?
		 */
		return 1;
	}

	return !priv.seen_other;
}