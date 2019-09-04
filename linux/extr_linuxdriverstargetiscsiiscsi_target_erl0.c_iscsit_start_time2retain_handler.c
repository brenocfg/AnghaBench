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
struct iscsi_session {int time2retain_timer_flags; TYPE_1__* sess_ops; int /*<<< orphan*/  time2retain_timer; int /*<<< orphan*/  sid; TYPE_2__* tpg; } ;
struct TYPE_4__ {scalar_t__ tpg_state; int /*<<< orphan*/  tpg_state_lock; } ;
struct TYPE_3__ {int DefaultTime2Retain; } ;

/* Variables and functions */
 int HZ ; 
 int ISCSI_TF_RUNNING ; 
 int ISCSI_TF_STOP ; 
 scalar_t__ TPG_STATE_ACTIVE ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void iscsit_start_time2retain_handler(struct iscsi_session *sess)
{
	int tpg_active;
	/*
	 * Only start Time2Retain timer when the associated TPG is still in
	 * an ACTIVE (eg: not disabled or shutdown) state.
	 */
	spin_lock(&sess->tpg->tpg_state_lock);
	tpg_active = (sess->tpg->tpg_state == TPG_STATE_ACTIVE);
	spin_unlock(&sess->tpg->tpg_state_lock);

	if (!tpg_active)
		return;

	if (sess->time2retain_timer_flags & ISCSI_TF_RUNNING)
		return;

	pr_debug("Starting Time2Retain timer for %u seconds on"
		" SID: %u\n", sess->sess_ops->DefaultTime2Retain, sess->sid);

	sess->time2retain_timer_flags &= ~ISCSI_TF_STOP;
	sess->time2retain_timer_flags |= ISCSI_TF_RUNNING;
	mod_timer(&sess->time2retain_timer,
		  jiffies + sess->sess_ops->DefaultTime2Retain * HZ);
}