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
struct zfcp_unit {int dummy; } ;
struct zfcp_scsi_dev {int /*<<< orphan*/  status; } ;
struct scsi_device {int dummy; } ;

/* Variables and functions */
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_device_put (struct scsi_device*) ; 
 struct zfcp_scsi_dev* sdev_to_zfcp (struct scsi_device*) ; 
 struct scsi_device* zfcp_unit_sdev (struct zfcp_unit*) ; 

unsigned int zfcp_unit_sdev_status(struct zfcp_unit *unit)
{
	unsigned int status = 0;
	struct scsi_device *sdev;
	struct zfcp_scsi_dev *zfcp_sdev;

	sdev = zfcp_unit_sdev(unit);
	if (sdev) {
		zfcp_sdev = sdev_to_zfcp(sdev);
		status = atomic_read(&zfcp_sdev->status);
		scsi_device_put(sdev);
	}

	return status;
}