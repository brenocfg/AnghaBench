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
struct scsi_cmnd {TYPE_1__* device; } ;
struct fc_lport {scalar_t__ state; int /*<<< orphan*/  link_up; } ;
struct fc_fcp_pkt {int dummy; } ;
struct fc_fcp_internal {int /*<<< orphan*/  scsi_queue_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 struct fc_fcp_pkt* CMD_SP (struct scsi_cmnd*) ; 
 int FAILED ; 
 scalar_t__ LPORT_ST_READY ; 
 int SUCCESS ; 
 int fc_block_scsi_eh (struct scsi_cmnd*) ; 
 scalar_t__ fc_fcp_lock_pkt (struct fc_fcp_pkt*) ; 
 int fc_fcp_pkt_abort (struct fc_fcp_pkt*) ; 
 int /*<<< orphan*/  fc_fcp_pkt_hold (struct fc_fcp_pkt*) ; 
 int /*<<< orphan*/  fc_fcp_pkt_release (struct fc_fcp_pkt*) ; 
 int /*<<< orphan*/  fc_fcp_unlock_pkt (struct fc_fcp_pkt*) ; 
 struct fc_fcp_internal* fc_get_scsi_internal (struct fc_lport*) ; 
 struct fc_lport* shost_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int fc_eh_abort(struct scsi_cmnd *sc_cmd)
{
	struct fc_fcp_pkt *fsp;
	struct fc_lport *lport;
	struct fc_fcp_internal *si;
	int rc = FAILED;
	unsigned long flags;
	int rval;

	rval = fc_block_scsi_eh(sc_cmd);
	if (rval)
		return rval;

	lport = shost_priv(sc_cmd->device->host);
	if (lport->state != LPORT_ST_READY)
		return rc;
	else if (!lport->link_up)
		return rc;

	si = fc_get_scsi_internal(lport);
	spin_lock_irqsave(&si->scsi_queue_lock, flags);
	fsp = CMD_SP(sc_cmd);
	if (!fsp) {
		/* command completed while scsi eh was setting up */
		spin_unlock_irqrestore(&si->scsi_queue_lock, flags);
		return SUCCESS;
	}
	/* grab a ref so the fsp and sc_cmd cannot be released from under us */
	fc_fcp_pkt_hold(fsp);
	spin_unlock_irqrestore(&si->scsi_queue_lock, flags);

	if (fc_fcp_lock_pkt(fsp)) {
		/* completed while we were waiting for timer to be deleted */
		rc = SUCCESS;
		goto release_pkt;
	}

	rc = fc_fcp_pkt_abort(fsp);
	fc_fcp_unlock_pkt(fsp);

release_pkt:
	fc_fcp_pkt_release(fsp);
	return rc;
}