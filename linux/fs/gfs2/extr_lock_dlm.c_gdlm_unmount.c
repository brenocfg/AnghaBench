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
struct lm_lockstruct {int /*<<< orphan*/ * ls_dlm; int /*<<< orphan*/  ls_recover_spin; int /*<<< orphan*/  ls_recover_flags; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_control_work; struct lm_lockstruct sd_lockstruct; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFL_NO_DLM_OPS ; 
 int /*<<< orphan*/  DFL_UNMOUNT ; 
 int /*<<< orphan*/  dlm_release_lockspace (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_recover_size (struct lm_lockstruct*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gdlm_unmount(struct gfs2_sbd *sdp)
{
	struct lm_lockstruct *ls = &sdp->sd_lockstruct;

	if (test_bit(DFL_NO_DLM_OPS, &ls->ls_recover_flags))
		goto release;

	/* wait for gfs2_control_wq to be done with this mount */

	spin_lock(&ls->ls_recover_spin);
	set_bit(DFL_UNMOUNT, &ls->ls_recover_flags);
	spin_unlock(&ls->ls_recover_spin);
	flush_delayed_work(&sdp->sd_control_work);

	/* mounted_lock and control_lock will be purged in dlm recovery */
release:
	if (ls->ls_dlm) {
		dlm_release_lockspace(ls->ls_dlm, 2);
		ls->ls_dlm = NULL;
	}

	free_recover_size(ls);
}