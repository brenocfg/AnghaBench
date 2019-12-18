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
struct ocfs2_lock_res {int /*<<< orphan*/  l_name; } ;
struct ocfs2_super {int /*<<< orphan*/  obs_trim_fs_mutex; struct ocfs2_lock_res osb_trim_fs_lockres; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_LOCK_TYPE_TRIM_FS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_build_lock_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_lock_res_init_common (struct ocfs2_super*,struct ocfs2_lock_res*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_lock_res_init_once (struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  ocfs2_trim_fs_lops ; 

void ocfs2_trim_fs_lock_res_init(struct ocfs2_super *osb)
{
	struct ocfs2_lock_res *lockres = &osb->osb_trim_fs_lockres;

	/* Only one trimfs thread are allowed to work at the same time. */
	mutex_lock(&osb->obs_trim_fs_mutex);

	ocfs2_lock_res_init_once(lockres);
	ocfs2_build_lock_name(OCFS2_LOCK_TYPE_TRIM_FS, 0, 0, lockres->l_name);
	ocfs2_lock_res_init_common(osb, lockres, OCFS2_LOCK_TYPE_TRIM_FS,
				   &ocfs2_trim_fs_lops, osb);
}