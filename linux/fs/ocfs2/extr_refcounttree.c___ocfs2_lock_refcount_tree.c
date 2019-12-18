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
struct ocfs2_super {int dummy; } ;
struct ocfs2_refcount_tree {int /*<<< orphan*/  rf_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_refcount_lock (struct ocfs2_refcount_tree*,int) ; 

__attribute__((used)) static int __ocfs2_lock_refcount_tree(struct ocfs2_super *osb,
				      struct ocfs2_refcount_tree *tree, int rw)
{
	int ret;

	ret = ocfs2_refcount_lock(tree, rw);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	if (rw)
		down_write(&tree->rf_sem);
	else
		down_read(&tree->rf_sem);

out:
	return ret;
}