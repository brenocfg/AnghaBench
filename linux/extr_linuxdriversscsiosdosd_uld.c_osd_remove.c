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
struct scsi_device {int dummy; } ;
struct TYPE_2__ {struct scsi_device* scsi_device; } ;
struct osd_uld_device {int /*<<< orphan*/  class_dev; int /*<<< orphan*/  minor; int /*<<< orphan*/  cdev; TYPE_1__ od; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSD_ERR (char*,struct device*,struct scsi_device*,struct scsi_device*) ; 
 int /*<<< orphan*/  cdev_device_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct osd_uld_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  ida_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osd_minor_ida ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static int osd_remove(struct device *dev)
{
	struct scsi_device *scsi_device = to_scsi_device(dev);
	struct osd_uld_device *oud = dev_get_drvdata(dev);

	if (oud->od.scsi_device != scsi_device) {
		OSD_ERR("Half cooked osd-device %p, || %p!=%p",
			dev, oud->od.scsi_device, scsi_device);
	}

	cdev_device_del(&oud->cdev, &oud->class_dev);
	ida_free(&osd_minor_ida, oud->minor);
	put_device(&oud->class_dev);

	return 0;
}