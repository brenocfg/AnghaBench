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
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_dentry_lock (struct dentry*,int) ; 
 int /*<<< orphan*/  ocfs2_dentry_unlock (struct dentry*,int) ; 

__attribute__((used)) static int ocfs2_remote_dentry_delete(struct dentry *dentry)
{
	int ret;

	ret = ocfs2_dentry_lock(dentry, 1);
	if (ret)
		mlog_errno(ret);
	else
		ocfs2_dentry_unlock(dentry, 1);

	return ret;
}