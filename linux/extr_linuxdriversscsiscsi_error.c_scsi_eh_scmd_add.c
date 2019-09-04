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
struct scsi_cmnd {int /*<<< orphan*/  rcu; int /*<<< orphan*/  eh_entry; TYPE_1__* device; } ;
struct Scsi_Host {int eh_deadline; int /*<<< orphan*/  host_lock; int /*<<< orphan*/  eh_cmd_q; scalar_t__ last_reset; int /*<<< orphan*/  ehandler; } ;
struct TYPE_2__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHOST_CANCEL_RECOVERY ; 
 int /*<<< orphan*/  SHOST_RECOVERY ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_eh_inc_host_failed ; 
 int /*<<< orphan*/  scsi_eh_reset (struct scsi_cmnd*) ; 
 int scsi_host_set_state (struct Scsi_Host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

void scsi_eh_scmd_add(struct scsi_cmnd *scmd)
{
	struct Scsi_Host *shost = scmd->device->host;
	unsigned long flags;
	int ret;

	WARN_ON_ONCE(!shost->ehandler);

	spin_lock_irqsave(shost->host_lock, flags);
	if (scsi_host_set_state(shost, SHOST_RECOVERY)) {
		ret = scsi_host_set_state(shost, SHOST_CANCEL_RECOVERY);
		WARN_ON_ONCE(ret);
	}
	if (shost->eh_deadline != -1 && !shost->last_reset)
		shost->last_reset = jiffies;

	scsi_eh_reset(scmd);
	list_add_tail(&scmd->eh_entry, &shost->eh_cmd_q);
	spin_unlock_irqrestore(shost->host_lock, flags);
	/*
	 * Ensure that all tasks observe the host state change before the
	 * host_failed change.
	 */
	call_rcu(&scmd->rcu, scsi_eh_inc_host_failed);
}