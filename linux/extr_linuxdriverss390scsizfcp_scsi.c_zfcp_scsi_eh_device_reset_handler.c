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
struct scsi_device {int dummy; } ;
struct scsi_cmnd {struct scsi_device* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCP_TMF_LUN_RESET ; 
 int zfcp_scsi_task_mgmt_function (struct scsi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zfcp_scsi_eh_device_reset_handler(struct scsi_cmnd *scpnt)
{
	struct scsi_device *sdev = scpnt->device;

	return zfcp_scsi_task_mgmt_function(sdev, FCP_TMF_LUN_RESET);
}