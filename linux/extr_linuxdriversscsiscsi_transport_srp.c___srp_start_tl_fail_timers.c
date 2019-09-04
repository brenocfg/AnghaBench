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
struct srp_rport {int reconnect_delay; int fast_io_fail_tmo; int dev_loss_tmo; int /*<<< orphan*/  dev_loss_work; int /*<<< orphan*/  fast_io_fail_work; int /*<<< orphan*/  state; int /*<<< orphan*/  reconnect_work; int /*<<< orphan*/  mutex; } ;
struct Scsi_Host {int /*<<< orphan*/  shost_gendev; } ;

/* Variables and functions */
 unsigned long HZ ; 
 int /*<<< orphan*/  SRP_RPORT_BLOCKED ; 
 int /*<<< orphan*/  SRP_RPORT_LOST ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 struct Scsi_Host* rport_to_shost (struct srp_rport*) ; 
 int /*<<< orphan*/  scsi_target_block (int /*<<< orphan*/ *) ; 
 scalar_t__ srp_rport_set_state (struct srp_rport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_long_wq ; 

__attribute__((used)) static void __srp_start_tl_fail_timers(struct srp_rport *rport)
{
	struct Scsi_Host *shost = rport_to_shost(rport);
	int delay, fast_io_fail_tmo, dev_loss_tmo;

	lockdep_assert_held(&rport->mutex);

	delay = rport->reconnect_delay;
	fast_io_fail_tmo = rport->fast_io_fail_tmo;
	dev_loss_tmo = rport->dev_loss_tmo;
	pr_debug("%s current state: %d\n", dev_name(&shost->shost_gendev),
		 rport->state);

	if (rport->state == SRP_RPORT_LOST)
		return;
	if (delay > 0)
		queue_delayed_work(system_long_wq, &rport->reconnect_work,
				   1UL * delay * HZ);
	if ((fast_io_fail_tmo >= 0 || dev_loss_tmo >= 0) &&
	    srp_rport_set_state(rport, SRP_RPORT_BLOCKED) == 0) {
		pr_debug("%s new state: %d\n", dev_name(&shost->shost_gendev),
			 rport->state);
		scsi_target_block(&shost->shost_gendev);
		if (fast_io_fail_tmo >= 0)
			queue_delayed_work(system_long_wq,
					   &rport->fast_io_fail_work,
					   1UL * fast_io_fail_tmo * HZ);
		if (dev_loss_tmo >= 0)
			queue_delayed_work(system_long_wq,
					   &rport->dev_loss_work,
					   1UL * dev_loss_tmo * HZ);
	}
}