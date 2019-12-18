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
struct ocfs2_lock_res {int dummy; } ;
struct ocfs2_super {int /*<<< orphan*/  obs_trim_fs_mutex; struct ocfs2_lock_res osb_trim_fs_lockres; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_lock_res_free (struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  ocfs2_simple_drop_lockres (struct ocfs2_super*,struct ocfs2_lock_res*) ; 

void ocfs2_trim_fs_lock_res_uninit(struct ocfs2_super *osb)
{
	struct ocfs2_lock_res *lockres = &osb->osb_trim_fs_lockres;

	ocfs2_simple_drop_lockres(osb, lockres);
	ocfs2_lock_res_free(lockres);

	mutex_unlock(&osb->obs_trim_fs_mutex);
}