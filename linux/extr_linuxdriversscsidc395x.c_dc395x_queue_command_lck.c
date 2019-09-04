#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct scsi_cmnd {int result; void (* scsi_done ) (struct scsi_cmnd*) ;TYPE_3__* device; int /*<<< orphan*/ * cmnd; } ;
struct ScsiReqBlk {int dummy; } ;
struct DeviceCtlBlk {int /*<<< orphan*/  srb_waiting_list; } ;
struct AdapterCtlBlk {int* dcb_map; TYPE_2__* scsi_host; } ;
struct TYPE_6__ {size_t id; int lun; TYPE_1__* host; } ;
struct TYPE_5__ {size_t max_id; int max_lun; } ;
struct TYPE_4__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_0 ; 
 int /*<<< orphan*/  DBG_1 ; 
 int DID_BAD_TARGET ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  build_srb (struct scsi_cmnd*,struct DeviceCtlBlk*,struct ScsiReqBlk*) ; 
 int /*<<< orphan*/  dprintkdbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dprintkl (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ) ; 
 struct DeviceCtlBlk* find_dcb (struct AdapterCtlBlk*,size_t,int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_srb (struct AdapterCtlBlk*,struct ScsiReqBlk*) ; 
 struct ScsiReqBlk* srb_get_free (struct AdapterCtlBlk*) ; 
 int /*<<< orphan*/  srb_waiting_append (struct DeviceCtlBlk*,struct ScsiReqBlk*) ; 
 int /*<<< orphan*/  waiting_process_next (struct AdapterCtlBlk*) ; 

__attribute__((used)) static int dc395x_queue_command_lck(struct scsi_cmnd *cmd, void (*done)(struct scsi_cmnd *))
{
	struct DeviceCtlBlk *dcb;
	struct ScsiReqBlk *srb;
	struct AdapterCtlBlk *acb =
	    (struct AdapterCtlBlk *)cmd->device->host->hostdata;
	dprintkdbg(DBG_0, "queue_command: (0x%p) <%02i-%i> cmnd=0x%02x\n",
		cmd, cmd->device->id, (u8)cmd->device->lun, cmd->cmnd[0]);

	/* Assume BAD_TARGET; will be cleared later */
	cmd->result = DID_BAD_TARGET << 16;

	/* ignore invalid targets */
	if (cmd->device->id >= acb->scsi_host->max_id ||
	    cmd->device->lun >= acb->scsi_host->max_lun ||
	    cmd->device->lun >31) {
		goto complete;
	}

	/* does the specified lun on the specified device exist */
	if (!(acb->dcb_map[cmd->device->id] & (1 << cmd->device->lun))) {
		dprintkl(KERN_INFO, "queue_command: Ignore target <%02i-%i>\n",
			cmd->device->id, (u8)cmd->device->lun);
		goto complete;
	}

	/* do we have a DCB for the device */
	dcb = find_dcb(acb, cmd->device->id, cmd->device->lun);
	if (!dcb) {
		/* should never happen */
		dprintkl(KERN_ERR, "queue_command: No such device <%02i-%i>",
			cmd->device->id, (u8)cmd->device->lun);
		goto complete;
	}

	/* set callback and clear result in the command */
	cmd->scsi_done = done;
	cmd->result = 0;

	srb = srb_get_free(acb);
	if (!srb)
	{
		/*
		 * Return 1 since we are unable to queue this command at this
		 * point in time.
		 */
		dprintkdbg(DBG_0, "queue_command: No free srb's\n");
		return 1;
	}

	build_srb(cmd, dcb, srb);

	if (!list_empty(&dcb->srb_waiting_list)) {
		/* append to waiting queue */
		srb_waiting_append(dcb, srb);
		waiting_process_next(acb);
	} else {
		/* process immediately */
		send_srb(acb, srb);
	}
	dprintkdbg(DBG_1, "queue_command: (0x%p) done\n", cmd);
	return 0;

complete:
	/*
	 * Complete the command immediatey, and then return 0 to
	 * indicate that we have handled the command. This is usually
	 * done when the commad is for things like non existent
	 * devices.
	 */
	done(cmd);
	return 0;
}