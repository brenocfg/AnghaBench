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
struct scsi_cmnd {TYPE_1__* device; } ;
struct Scsi_Host {TYPE_2__* hostt; } ;
struct TYPE_4__ {int (* eh_device_reset_handler ) (struct scsi_cmnd*) ;int (* eh_target_reset_handler ) (struct scsi_cmnd*) ;} ;
struct TYPE_3__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 int FAILED ; 
 int SUCCESS ; 
 int stub1 (struct scsi_cmnd*) ; 
 int stub2 (struct scsi_cmnd*) ; 

__attribute__((used)) static int try_to_reset_cmd_device(struct scsi_cmnd *cmd)
{
	int res;
	struct Scsi_Host *shost = cmd->device->host;

	if (!shost->hostt->eh_device_reset_handler)
		goto try_target_reset;

	res = shost->hostt->eh_device_reset_handler(cmd);
	if (res == SUCCESS)
		return res;

try_target_reset:
	if (shost->hostt->eh_target_reset_handler)
		return shost->hostt->eh_target_reset_handler(cmd);

	return FAILED;
}