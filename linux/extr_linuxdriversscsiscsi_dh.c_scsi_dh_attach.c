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
struct scsi_device_handler {int dummy; } ;
struct scsi_device {int /*<<< orphan*/  sdev_gendev; struct scsi_device_handler* handler; } ;
struct request_queue {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 struct scsi_device* scsi_device_from_queue (struct request_queue*) ; 
 int scsi_dh_handler_attach (struct scsi_device*,struct scsi_device_handler*) ; 
 struct scsi_device_handler* scsi_dh_lookup (char const*) ; 

int scsi_dh_attach(struct request_queue *q, const char *name)
{
	struct scsi_device *sdev;
	struct scsi_device_handler *scsi_dh;
	int err = 0;

	sdev = scsi_device_from_queue(q);
	if (!sdev)
		return -ENODEV;

	scsi_dh = scsi_dh_lookup(name);
	if (!scsi_dh) {
		err = -EINVAL;
		goto out_put_device;
	}

	if (sdev->handler) {
		if (sdev->handler != scsi_dh)
			err = -EBUSY;
		goto out_put_device;
	}

	err = scsi_dh_handler_attach(sdev, scsi_dh);

out_put_device:
	put_device(&sdev->sdev_gendev);
	return err;
}