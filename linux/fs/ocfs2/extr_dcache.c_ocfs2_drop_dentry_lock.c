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
struct ocfs2_dentry_lock {int /*<<< orphan*/  dl_lockres; int /*<<< orphan*/  dl_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ocfs2_dentry_lock*) ; 
 int /*<<< orphan*/  ocfs2_lock_res_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_simple_drop_lockres (struct ocfs2_super*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ocfs2_drop_dentry_lock(struct ocfs2_super *osb,
				   struct ocfs2_dentry_lock *dl)
{
	iput(dl->dl_inode);
	ocfs2_simple_drop_lockres(osb, &dl->dl_lockres);
	ocfs2_lock_res_free(&dl->dl_lockres);
	kfree(dl);
}