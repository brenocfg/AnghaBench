#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  event; int /*<<< orphan*/  dead_node; int /*<<< orphan*/  new_master; int /*<<< orphan*/  state; } ;
struct dlm_ctxt {TYPE_1__ reco; int /*<<< orphan*/  dlm_reco_thread_task; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ dlm_in_recovery (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_pid_nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void dlm_wait_for_recovery(struct dlm_ctxt *dlm)
{
	if (dlm_in_recovery(dlm)) {
		mlog(0, "%s: reco thread %d in recovery: "
		     "state=%d, master=%u, dead=%u\n",
		     dlm->name, task_pid_nr(dlm->dlm_reco_thread_task),
		     dlm->reco.state, dlm->reco.new_master,
		     dlm->reco.dead_node);
	}
	wait_event(dlm->reco.event, !dlm_in_recovery(dlm));
}