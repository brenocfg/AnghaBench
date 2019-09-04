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
struct srb {int /*<<< orphan*/ * wait; struct scsi_cmnd* cmd; } ;
struct scsi_qla_host {TYPE_1__* host; } ;
struct scsi_cmnd {int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;} ;
struct completion {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 scalar_t__ CMD_HANDLE (struct scsi_cmnd*) ; 
 scalar_t__ COMPLETED_HANDLE ; 
 int FAILED ; 
 int HZ ; 
 int SUCCESS ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (struct completion*,int) ; 

__attribute__((used)) static int
_qla1280_wait_for_single_command(struct scsi_qla_host *ha, struct srb *sp,
				 struct completion *wait)
{
	int	status = FAILED;
	struct scsi_cmnd *cmd = sp->cmd;

	spin_unlock_irq(ha->host->host_lock);
	wait_for_completion_timeout(wait, 4*HZ);
	spin_lock_irq(ha->host->host_lock);
	sp->wait = NULL;
	if(CMD_HANDLE(cmd) == COMPLETED_HANDLE) {
		status = SUCCESS;
		(*cmd->scsi_done)(cmd);
	}
	return status;
}