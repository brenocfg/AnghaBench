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
struct scsi_host_template {int (* eh_device_reset_handler ) (struct scsi_cmnd*) ;} ;
struct scsi_cmnd {TYPE_2__* device; } ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {struct scsi_host_template* hostt; } ;

/* Variables and functions */
 int FAILED ; 
 int SUCCESS ; 
 int /*<<< orphan*/  __scsi_report_device_reset (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static int scsi_try_bus_device_reset(struct scsi_cmnd *scmd)
{
	int rtn;
	struct scsi_host_template *hostt = scmd->device->host->hostt;

	if (!hostt->eh_device_reset_handler)
		return FAILED;

	rtn = hostt->eh_device_reset_handler(scmd);
	if (rtn == SUCCESS)
		__scsi_report_device_reset(scmd->device, NULL);
	return rtn;
}