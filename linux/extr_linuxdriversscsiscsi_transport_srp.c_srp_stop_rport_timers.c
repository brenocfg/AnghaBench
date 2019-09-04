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
struct srp_rport {scalar_t__ state; int /*<<< orphan*/  dev_loss_work; int /*<<< orphan*/  fast_io_fail_work; int /*<<< orphan*/  reconnect_work; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 scalar_t__ SRP_RPORT_BLOCKED ; 
 int /*<<< orphan*/  SRP_RPORT_LOST ; 
 int /*<<< orphan*/  __rport_fail_io_fast (struct srp_rport*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srp_rport_set_state (struct srp_rport*,int /*<<< orphan*/ ) ; 

void srp_stop_rport_timers(struct srp_rport *rport)
{
	mutex_lock(&rport->mutex);
	if (rport->state == SRP_RPORT_BLOCKED)
		__rport_fail_io_fast(rport);
	srp_rport_set_state(rport, SRP_RPORT_LOST);
	mutex_unlock(&rport->mutex);

	cancel_delayed_work_sync(&rport->reconnect_work);
	cancel_delayed_work_sync(&rport->fast_io_fail_work);
	cancel_delayed_work_sync(&rport->dev_loss_work);
}