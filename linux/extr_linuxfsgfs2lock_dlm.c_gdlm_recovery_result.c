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
struct lm_lockstruct {unsigned int ls_jid; unsigned int ls_recover_size; unsigned int* ls_recover_result; int /*<<< orphan*/  ls_recover_spin; int /*<<< orphan*/  ls_recover_flags; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_control_work; struct lm_lockstruct sd_lockstruct; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFL_FIRST_MOUNT ; 
 int /*<<< orphan*/  DFL_NO_DLM_OPS ; 
 int /*<<< orphan*/  DFL_UNMOUNT ; 
 int /*<<< orphan*/  HZ ; 
 unsigned int LM_RD_GAVEUP ; 
 int /*<<< orphan*/  fs_err (struct gfs2_sbd*,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  fs_info (struct gfs2_sbd*,char*,unsigned int,char*) ; 
 int /*<<< orphan*/  gfs2_control_wq ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gdlm_recovery_result(struct gfs2_sbd *sdp, unsigned int jid,
				 unsigned int result)
{
	struct lm_lockstruct *ls = &sdp->sd_lockstruct;

	if (test_bit(DFL_NO_DLM_OPS, &ls->ls_recover_flags))
		return;

	/* don't care about the recovery of own journal during mount */
	if (jid == ls->ls_jid)
		return;

	spin_lock(&ls->ls_recover_spin);
	if (test_bit(DFL_FIRST_MOUNT, &ls->ls_recover_flags)) {
		spin_unlock(&ls->ls_recover_spin);
		return;
	}
	if (ls->ls_recover_size < jid + 1) {
		fs_err(sdp, "recovery_result jid %d short size %d\n",
		       jid, ls->ls_recover_size);
		spin_unlock(&ls->ls_recover_spin);
		return;
	}

	fs_info(sdp, "recover jid %d result %s\n", jid,
		result == LM_RD_GAVEUP ? "busy" : "success");

	ls->ls_recover_result[jid] = result;

	/* GAVEUP means another node is recovering the journal; delay our
	   next attempt to recover it, to give the other node a chance to
	   finish before trying again */

	if (!test_bit(DFL_UNMOUNT, &ls->ls_recover_flags))
		queue_delayed_work(gfs2_control_wq, &sdp->sd_control_work,
				   result == LM_RD_GAVEUP ? HZ : 0);
	spin_unlock(&ls->ls_recover_spin);
}