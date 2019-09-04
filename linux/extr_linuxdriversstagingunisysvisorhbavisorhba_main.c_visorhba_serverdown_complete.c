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
struct visorhba_devdata {int serverdown; int serverchangingstate; int /*<<< orphan*/  privlock; int /*<<< orphan*/  idr; struct scsipending* pending; int /*<<< orphan*/  thread; } ;
struct uiscmdrsp {int result; int /*<<< orphan*/  (* scsi_done ) (struct uiscmdrsp*) ;} ;
struct scsipending {int cmdtype; struct uiscmdrsp* sent; } ;
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct uiscmdrsp*) ;} ;

/* Variables and functions */
#define  CMD_SCSITASKMGMT_TYPE 129 
#define  CMD_SCSI_TYPE 128 
 int DID_RESET ; 
 int MAX_PENDING_REQUESTS ; 
 int /*<<< orphan*/  TASK_MGMT_FAILED ; 
 int /*<<< orphan*/  complete_taskmgmt_command (int /*<<< orphan*/ *,struct uiscmdrsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct uiscmdrsp*) ; 
 int /*<<< orphan*/  visor_thread_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void visorhba_serverdown_complete(struct visorhba_devdata *devdata)
{
	int i;
	struct scsipending *pendingdel = NULL;
	struct scsi_cmnd *scsicmd = NULL;
	struct uiscmdrsp *cmdrsp;
	unsigned long flags;

	/* Stop using the IOVM response queue (queue should be drained
	 * by the end)
	 */
	visor_thread_stop(devdata->thread);

	/* Fail commands that weren't completed */
	spin_lock_irqsave(&devdata->privlock, flags);
	for (i = 0; i < MAX_PENDING_REQUESTS; i++) {
		pendingdel = &devdata->pending[i];
		switch (pendingdel->cmdtype) {
		case CMD_SCSI_TYPE:
			scsicmd = pendingdel->sent;
			scsicmd->result = DID_RESET << 16;
			if (scsicmd->scsi_done)
				scsicmd->scsi_done(scsicmd);
			break;
		case CMD_SCSITASKMGMT_TYPE:
			cmdrsp = pendingdel->sent;
			complete_taskmgmt_command(&devdata->idr, cmdrsp,
						  TASK_MGMT_FAILED);
			break;
		default:
			break;
		}
		pendingdel->cmdtype = 0;
		pendingdel->sent = NULL;
	}
	spin_unlock_irqrestore(&devdata->privlock, flags);

	devdata->serverdown = true;
	devdata->serverchangingstate = false;
}