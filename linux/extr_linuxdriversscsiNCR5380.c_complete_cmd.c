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
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;TYPE_1__* device; } ;
struct Scsi_Host {int dummy; } ;
struct NCR5380_hostdata {int* busy; struct scsi_cmnd* sensing; int /*<<< orphan*/  ses; } ;
struct TYPE_2__ {int lun; } ;

/* Variables and functions */
 int /*<<< orphan*/  DID_ERROR ; 
 int /*<<< orphan*/  NDEBUG_QUEUES ; 
 int SAM_STAT_GOOD ; 
 int /*<<< orphan*/  dsprintk (int /*<<< orphan*/ ,struct Scsi_Host*,char*,struct scsi_cmnd*) ; 
 size_t scmd_id (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_eh_restore_cmnd (struct scsi_cmnd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_host_byte (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 struct NCR5380_hostdata* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void complete_cmd(struct Scsi_Host *instance,
                         struct scsi_cmnd *cmd)
{
	struct NCR5380_hostdata *hostdata = shost_priv(instance);

	dsprintk(NDEBUG_QUEUES, instance, "complete_cmd: cmd %p\n", cmd);

	if (hostdata->sensing == cmd) {
		/* Autosense processing ends here */
		if ((cmd->result & 0xff) != SAM_STAT_GOOD) {
			scsi_eh_restore_cmnd(cmd, &hostdata->ses);
			set_host_byte(cmd, DID_ERROR);
		} else
			scsi_eh_restore_cmnd(cmd, &hostdata->ses);
		hostdata->sensing = NULL;
	}

	hostdata->busy[scmd_id(cmd)] &= ~(1 << cmd->device->lun);

	cmd->scsi_done(cmd);
}