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
struct ocfs2_dentry_lock {int dl_count; int /*<<< orphan*/  dl_lockres; } ;
struct inode {int dummy; } ;
struct dentry {struct ocfs2_dentry_lock* d_fsdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  dentry_attach_lock ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct ocfs2_dentry_lock*) ; 
 int /*<<< orphan*/  ocfs2_lock_res_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_simple_drop_lockres (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ocfs2_cleanup_add_entry_failure(struct ocfs2_super *osb,
		struct dentry *dentry, struct inode *inode)
{
	struct ocfs2_dentry_lock *dl = dentry->d_fsdata;

	ocfs2_simple_drop_lockres(osb, &dl->dl_lockres);
	ocfs2_lock_res_free(&dl->dl_lockres);
	BUG_ON(dl->dl_count != 1);
	spin_lock(&dentry_attach_lock);
	dentry->d_fsdata = NULL;
	spin_unlock(&dentry_attach_lock);
	kfree(dl);
	iput(inode);
}