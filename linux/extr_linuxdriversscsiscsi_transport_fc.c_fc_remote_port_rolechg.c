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
typedef  int u32 ;
struct fc_rport {int scsi_target_id; int roles; int flags; int /*<<< orphan*/  scan_work; int /*<<< orphan*/  dev; int /*<<< orphan*/  dev_loss_work; int /*<<< orphan*/  fail_io_work; } ;
struct fc_host_attrs {int /*<<< orphan*/  next_target_id; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int FC_PORT_ROLE_FCP_TARGET ; 
 int FC_RPORT_DEVLOSS_CALLBK_DONE ; 
 int FC_RPORT_DEVLOSS_PENDING ; 
 int FC_RPORT_FAST_FAIL_TIMEDOUT ; 
 int FC_RPORT_SCAN_PENDING ; 
 int /*<<< orphan*/  SDEV_RUNNING ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fc_flush_devloss (struct Scsi_Host*) ; 
 int /*<<< orphan*/  fc_flush_work (struct Scsi_Host*) ; 
 struct Scsi_Host* rport_to_shost (struct fc_rport*) ; 
 int /*<<< orphan*/  scsi_queue_work (struct Scsi_Host*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_target_unblock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct fc_host_attrs* shost_to_fc_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

void
fc_remote_port_rolechg(struct fc_rport  *rport, u32 roles)
{
	struct Scsi_Host *shost = rport_to_shost(rport);
	struct fc_host_attrs *fc_host = shost_to_fc_host(shost);
	unsigned long flags;
	int create = 0;

	spin_lock_irqsave(shost->host_lock, flags);
	if (roles & FC_PORT_ROLE_FCP_TARGET) {
		if (rport->scsi_target_id == -1) {
			rport->scsi_target_id = fc_host->next_target_id++;
			create = 1;
		} else if (!(rport->roles & FC_PORT_ROLE_FCP_TARGET))
			create = 1;
	}

	rport->roles = roles;

	spin_unlock_irqrestore(shost->host_lock, flags);

	if (create) {
		/*
		 * There may have been a delete timer running on the
		 * port. Ensure that it is cancelled as we now know
		 * the port is an FCP Target.
		 * Note: we know the rport exists and is in an online
		 *  state as the LLDD would not have had an rport
		 *  reference to pass us.
		 *
		 * Take no action on the del_timer failure as the state
		 * machine state change will validate the
		 * transaction.
		 */
		if (!cancel_delayed_work(&rport->fail_io_work))
			fc_flush_devloss(shost);
		if (!cancel_delayed_work(&rport->dev_loss_work))
			fc_flush_devloss(shost);

		spin_lock_irqsave(shost->host_lock, flags);
		rport->flags &= ~(FC_RPORT_FAST_FAIL_TIMEDOUT |
				  FC_RPORT_DEVLOSS_PENDING |
				  FC_RPORT_DEVLOSS_CALLBK_DONE);
		spin_unlock_irqrestore(shost->host_lock, flags);

		/* ensure any stgt delete functions are done */
		fc_flush_work(shost);

		scsi_target_unblock(&rport->dev, SDEV_RUNNING);
		/* initiate a scan of the target */
		spin_lock_irqsave(shost->host_lock, flags);
		rport->flags |= FC_RPORT_SCAN_PENDING;
		scsi_queue_work(shost, &rport->scan_work);
		spin_unlock_irqrestore(shost->host_lock, flags);
	}
}