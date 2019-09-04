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
struct scsi_host_template {int (* eh_host_reset_handler ) (struct scsi_cmnd*) ;int /*<<< orphan*/  skip_settle_delay; } ;
struct scsi_cmnd {TYPE_1__* device; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; struct scsi_host_template* hostt; } ;
struct TYPE_2__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 int FAILED ; 
 int /*<<< orphan*/  HOST_RESET_SETTLE_TIME ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  SCSI_LOG_ERROR_RECOVERY (int,int /*<<< orphan*/ ) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  scmd_channel (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_report_bus_reset (struct Scsi_Host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,struct Scsi_Host*,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ssleep (int /*<<< orphan*/ ) ; 
 int stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static int scsi_try_host_reset(struct scsi_cmnd *scmd)
{
	unsigned long flags;
	int rtn;
	struct Scsi_Host *host = scmd->device->host;
	struct scsi_host_template *hostt = host->hostt;

	SCSI_LOG_ERROR_RECOVERY(3,
		shost_printk(KERN_INFO, host, "Snd Host RST\n"));

	if (!hostt->eh_host_reset_handler)
		return FAILED;

	rtn = hostt->eh_host_reset_handler(scmd);

	if (rtn == SUCCESS) {
		if (!hostt->skip_settle_delay)
			ssleep(HOST_RESET_SETTLE_TIME);
		spin_lock_irqsave(host->host_lock, flags);
		scsi_report_bus_reset(host, scmd_channel(scmd));
		spin_unlock_irqrestore(host->host_lock, flags);
	}

	return rtn;
}