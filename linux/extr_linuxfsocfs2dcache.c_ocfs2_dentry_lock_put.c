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
struct ocfs2_dentry_lock {scalar_t__ dl_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  dentry_attach_lock ; 
 int /*<<< orphan*/  ocfs2_drop_dentry_lock (struct ocfs2_super*,struct ocfs2_dentry_lock*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ocfs2_dentry_lock_put(struct ocfs2_super *osb,
			   struct ocfs2_dentry_lock *dl)
{
	int unlock = 0;

	BUG_ON(dl->dl_count == 0);

	spin_lock(&dentry_attach_lock);
	dl->dl_count--;
	unlock = !dl->dl_count;
	spin_unlock(&dentry_attach_lock);

	if (unlock)
		ocfs2_drop_dentry_lock(osb, dl);
}