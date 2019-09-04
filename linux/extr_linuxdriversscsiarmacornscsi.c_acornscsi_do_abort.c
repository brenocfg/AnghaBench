#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int /*<<< orphan*/  tag; } ;
typedef  enum res_abort { ____Placeholder_res_abort } res_abort ;
struct TYPE_8__ {int phase; int /*<<< orphan*/  disconnectable; } ;
struct TYPE_7__ {int /*<<< orphan*/  disconnected; int /*<<< orphan*/  issue; } ;
struct TYPE_9__ {struct scsi_cmnd* origSCpnt; struct scsi_cmnd* SCpnt; TYPE_2__ scsi; TYPE_1__ queues; } ;
typedef  TYPE_3__ AS_Host ;

/* Variables and functions */
 int /*<<< orphan*/  CMND_DISCONNECT ; 
#define  PHASE_CONNECTED 129 
#define  PHASE_IDLE 128 
 int /*<<< orphan*/  SBIC_CMND ; 
 int /*<<< orphan*/  acornscsi_abortcmd (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  printk (char*) ; 
 scalar_t__ queue_remove_cmd (int /*<<< orphan*/ *,struct scsi_cmnd*) ; 
 int res_not_running ; 
 int res_snooze ; 
 int res_success ; 
 int res_success_clear ; 
 int /*<<< orphan*/  sbic_arm_write (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum res_abort acornscsi_do_abort(AS_Host *host, struct scsi_cmnd *SCpnt)
{
	enum res_abort res = res_not_running;

	if (queue_remove_cmd(&host->queues.issue, SCpnt)) {
		/*
		 * The command was on the issue queue, and has not been
		 * issued yet.  We can remove the command from the queue,
		 * and acknowledge the abort.  Neither the devices nor the
		 * interface know about the command.
		 */
//#if (DEBUG & DEBUG_ABORT)
		printk("on issue queue ");
//#endif
		res = res_success;
	} else if (queue_remove_cmd(&host->queues.disconnected, SCpnt)) {
		/*
		 * The command was on the disconnected queue.  Simply
		 * acknowledge the abort condition, and when the target
		 * reconnects, we will give it an ABORT message.  The
		 * target should then disconnect, and we will clear
		 * the busylun bit.
		 */
//#if (DEBUG & DEBUG_ABORT)
		printk("on disconnected queue ");
//#endif
		res = res_success;
	} else if (host->SCpnt == SCpnt) {
		unsigned long flags;

//#if (DEBUG & DEBUG_ABORT)
		printk("executing ");
//#endif

		local_irq_save(flags);
		switch (host->scsi.phase) {
		/*
		 * If the interface is idle, and the command is 'disconnectable',
		 * then it is the same as on the disconnected queue.  We simply
		 * remove all traces of the command.  When the target reconnects,
		 * we will give it an ABORT message since the command could not
		 * be found.  When the target finally disconnects, we will clear
		 * the busylun bit.
		 */
		case PHASE_IDLE:
			if (host->scsi.disconnectable) {
				host->scsi.disconnectable = 0;
				host->SCpnt = NULL;
				res = res_success;
			}
			break;

		/*
		 * If the command has connected and done nothing further,
		 * simply force a disconnect.  We also need to clear the
		 * busylun bit.
		 */
		case PHASE_CONNECTED:
			sbic_arm_write(host, SBIC_CMND, CMND_DISCONNECT);
			host->SCpnt = NULL;
			res = res_success_clear;
			break;

		default:
			acornscsi_abortcmd(host, host->SCpnt->tag);
			res = res_snooze;
		}
		local_irq_restore(flags);
	} else if (host->origSCpnt == SCpnt) {
		/*
		 * The command will be executed next, but a command
		 * is currently using the interface.  This is similar to
		 * being on the issue queue, except the busylun bit has
		 * been set.
		 */
		host->origSCpnt = NULL;
//#if (DEBUG & DEBUG_ABORT)
		printk("waiting for execution ");
//#endif
		res = res_success_clear;
	} else
		printk("unknown ");

	return res;
}