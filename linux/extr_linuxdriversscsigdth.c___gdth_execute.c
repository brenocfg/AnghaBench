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
typedef  int /*<<< orphan*/  u32 ;
struct scsi_device {int /*<<< orphan*/  host; } ;
struct scsi_cmnd {int cmd_len; char* cmnd; struct scsi_cmnd* sense_buffer; struct request* request; struct scsi_device* device; } ;
struct request {int dummy; } ;
struct gdth_cmndinfo {int internal_command; int status; int /*<<< orphan*/  info; int /*<<< orphan*/ * internal_cmd_str; int /*<<< orphan*/  priority; } ;
typedef  int /*<<< orphan*/  gdth_ha_str ;
typedef  int /*<<< orphan*/  gdth_cmd_str ;
typedef  int /*<<< orphan*/  cmndinfo ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IOCTL_PRI ; 
 int SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  __gdth_queuecommand (int /*<<< orphan*/ *,struct scsi_cmnd*,struct gdth_cmndinfo*) ; 
 int /*<<< orphan*/  kfree (struct scsi_cmnd*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct gdth_cmndinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * shost_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int __gdth_execute(struct scsi_device *sdev, gdth_cmd_str *gdtcmd, char *cmnd,
                   int timeout, u32 *info)
{
    gdth_ha_str *ha = shost_priv(sdev->host);
    struct scsi_cmnd *scp;
    struct gdth_cmndinfo cmndinfo;
    DECLARE_COMPLETION_ONSTACK(wait);
    int rval;

    scp = kzalloc(sizeof(*scp), GFP_KERNEL);
    if (!scp)
        return -ENOMEM;

    scp->sense_buffer = kzalloc(SCSI_SENSE_BUFFERSIZE, GFP_KERNEL);
    if (!scp->sense_buffer) {
	kfree(scp);
	return -ENOMEM;
    }

    scp->device = sdev;
    memset(&cmndinfo, 0, sizeof(cmndinfo));

    /* use request field to save the ptr. to completion struct. */
    scp->request = (struct request *)&wait;
    scp->cmd_len = 12;
    scp->cmnd = cmnd;
    cmndinfo.priority = IOCTL_PRI;
    cmndinfo.internal_cmd_str = gdtcmd;
    cmndinfo.internal_command = 1;

    TRACE(("__gdth_execute() cmd 0x%x\n", scp->cmnd[0]));
    __gdth_queuecommand(ha, scp, &cmndinfo);

    wait_for_completion(&wait);

    rval = cmndinfo.status;
    if (info)
        *info = cmndinfo.info;
    kfree(scp->sense_buffer);
    kfree(scp);
    return rval;
}