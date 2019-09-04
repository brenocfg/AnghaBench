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
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__ cmd_per_lun; scalar_t__ can_queue; } ;

/* Variables and functions */
 scalar_t__ ISCSI_DEF_CMD_PER_LUN ; 
 scalar_t__ ISCSI_DEF_XMIT_CMDS_MAX ; 
 int scsi_add_host (struct Scsi_Host*,struct device*) ; 

int iscsi_host_add(struct Scsi_Host *shost, struct device *pdev)
{
	if (!shost->can_queue)
		shost->can_queue = ISCSI_DEF_XMIT_CMDS_MAX;

	if (!shost->cmd_per_lun)
		shost->cmd_per_lun = ISCSI_DEF_CMD_PER_LUN;

	return scsi_add_host(shost, pdev);
}