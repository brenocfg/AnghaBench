#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct scsi_device {scalar_t__ type; } ;
struct TYPE_7__ {int /*<<< orphan*/  release; struct device* parent; int /*<<< orphan*/ * class; int /*<<< orphan*/  devt; } ;
struct TYPE_8__ {int /*<<< orphan*/  owner; } ;
struct osd_uld_device {int minor; TYPE_1__ class_dev; TYPE_4__ cdev; struct gendisk* disk; int /*<<< orphan*/  od; } ;
struct gendisk {int first_minor; int /*<<< orphan*/  disk_name; int /*<<< orphan*/  major; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OSD_ERR (char*,...) ; 
 int /*<<< orphan*/  OSD_INFO (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCSI_OSD_MAJOR ; 
 int /*<<< orphan*/  SCSI_OSD_MAX_MINOR ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ TYPE_OSD ; 
 int __detect_osd (struct osd_uld_device*) ; 
 int /*<<< orphan*/  __remove ; 
 struct gendisk* alloc_disk (int) ; 
 int cdev_device_add (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  cdev_init (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct osd_uld_device*) ; 
 int dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int ida_alloc_max (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_free (int /*<<< orphan*/ *,int) ; 
 struct osd_uld_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osd_dev_init (int /*<<< orphan*/ *,struct scsi_device*) ; 
 int /*<<< orphan*/  osd_fops ; 
 int /*<<< orphan*/  osd_minor_ida ; 
 int /*<<< orphan*/  osd_uld_class ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 scalar_t__ scsi_device_get (struct scsi_device*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static int osd_probe(struct device *dev)
{
	struct scsi_device *scsi_device = to_scsi_device(dev);
	struct gendisk *disk;
	struct osd_uld_device *oud;
	int minor;
	int error;

	if (scsi_device->type != TYPE_OSD)
		return -ENODEV;

	minor = ida_alloc_max(&osd_minor_ida, SCSI_OSD_MAX_MINOR, GFP_KERNEL);
	if (minor == -ENOSPC)
		return -EBUSY;
	if (minor < 0)
		return -ENODEV;

	error = -ENOMEM;
	oud = kzalloc(sizeof(*oud), GFP_KERNEL);
	if (NULL == oud)
		goto err_retract_minor;

	/* class device member */
	device_initialize(&oud->class_dev);
	dev_set_drvdata(dev, oud);
	oud->minor = minor;
	oud->class_dev.devt = MKDEV(SCSI_OSD_MAJOR, oud->minor);
	oud->class_dev.class = &osd_uld_class;
	oud->class_dev.parent = dev;
	oud->class_dev.release = __remove;

	/* hold one more reference to the scsi_device that will get released
	 * in __release, in case a logout is happening while fs is mounted
	 */
	if (scsi_device_get(scsi_device))
		goto err_retract_minor;
	osd_dev_init(&oud->od, scsi_device);

	/* allocate a disk and set it up */
	/* FIXME: do we need this since sg has already done that */
	disk = alloc_disk(1);
	if (!disk) {
		OSD_ERR("alloc_disk failed\n");
		goto err_free_osd;
	}
	disk->major = SCSI_OSD_MAJOR;
	disk->first_minor = oud->minor;
	sprintf(disk->disk_name, "osd%d", oud->minor);
	oud->disk = disk;

	/* Detect the OSD Version */
	error = __detect_osd(oud);
	if (error) {
		OSD_ERR("osd detection failed, non-compatible OSD device\n");
		goto err_free_osd;
	}

	/* init the char-device for communication with user-mode */
	cdev_init(&oud->cdev, &osd_fops);
	oud->cdev.owner = THIS_MODULE;

	error = dev_set_name(&oud->class_dev, "%s", disk->disk_name);
	if (error) {
		OSD_ERR("dev_set_name failed => %d\n", error);
		goto err_free_osd;
	}

	error = cdev_device_add(&oud->cdev, &oud->class_dev);
	if (error) {
		OSD_ERR("device_register failed => %d\n", error);
		goto err_free_osd;
	}

	OSD_INFO("osd_probe %s\n", disk->disk_name);
	return 0;

err_free_osd:
	put_device(&oud->class_dev);
err_retract_minor:
	ida_free(&osd_minor_ida, minor);
	return error;
}