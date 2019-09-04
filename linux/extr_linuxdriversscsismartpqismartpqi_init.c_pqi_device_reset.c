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
struct pqi_scsi_dev {int dummy; } ;
struct pqi_ctrl_info {int dummy; } ;

/* Variables and functions */
 int FAILED ; 
 int SUCCESS ; 
 int pqi_device_wait_for_pending_io (struct pqi_ctrl_info*,struct pqi_scsi_dev*) ; 
 int pqi_lun_reset (struct pqi_ctrl_info*,struct pqi_scsi_dev*) ; 

__attribute__((used)) static int pqi_device_reset(struct pqi_ctrl_info *ctrl_info,
	struct pqi_scsi_dev *device)
{
	int rc;

	rc = pqi_lun_reset(ctrl_info, device);
	if (rc == 0)
		rc = pqi_device_wait_for_pending_io(ctrl_info, device);

	return rc == 0 ? SUCCESS : FAILED;
}