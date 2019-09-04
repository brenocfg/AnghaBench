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
struct scsi_cmnd {TYPE_2__* device; } ;
struct ipr_ioa_cfg {int dummy; } ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {int /*<<< orphan*/  host_lock; scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  LEAVE ; 
 int SUCCESS ; 
 int ipr_cancel_op (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  ipr_match_lun ; 
 int ipr_wait_for_ops (struct ipr_ioa_cfg*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int ipr_eh_abort(struct scsi_cmnd *scsi_cmd)
{
	unsigned long flags;
	int rc;
	struct ipr_ioa_cfg *ioa_cfg;

	ENTER;

	ioa_cfg = (struct ipr_ioa_cfg *) scsi_cmd->device->host->hostdata;

	spin_lock_irqsave(scsi_cmd->device->host->host_lock, flags);
	rc = ipr_cancel_op(scsi_cmd);
	spin_unlock_irqrestore(scsi_cmd->device->host->host_lock, flags);

	if (rc == SUCCESS)
		rc = ipr_wait_for_ops(ioa_cfg, scsi_cmd->device, ipr_match_lun);
	LEAVE;
	return rc;
}