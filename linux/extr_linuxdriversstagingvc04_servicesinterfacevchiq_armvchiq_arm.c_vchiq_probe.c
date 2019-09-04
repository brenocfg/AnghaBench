#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rpi_firmware {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_NAME ; 
 int ENOENT ; 
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  VCHIQ_MINOR ; 
 int /*<<< orphan*/  VCHIQ_VERSION ; 
 int /*<<< orphan*/  VCHIQ_VERSION_MIN ; 
 int alloc_chrdev_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bcm2835_camera ; 
 int /*<<< orphan*/ * bcm2835_codec ; 
 int cdev_add (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_del (TYPE_1__*) ; 
 int /*<<< orphan*/  cdev_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * class_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  class_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * device_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  g_state ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rpi_firmware*) ; 
 struct rpi_firmware* rpi_firmware_get (struct device_node*) ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vchiq_arm_log_level ; 
 TYPE_1__ vchiq_cdev ; 
 int /*<<< orphan*/ * vchiq_class ; 
 int /*<<< orphan*/  vchiq_debugfs_init () ; 
 int /*<<< orphan*/ * vchiq_dev ; 
 int /*<<< orphan*/  vchiq_devid ; 
 int /*<<< orphan*/  vchiq_fops ; 
 int /*<<< orphan*/  vchiq_log_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vchiq_log_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_log_warning (int /*<<< orphan*/ ,char*) ; 
 int vchiq_platform_init (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vchiq_register_child (struct platform_device*,char*) ; 
 int /*<<< orphan*/ * vcsm_cma ; 

__attribute__((used)) static int vchiq_probe(struct platform_device *pdev)
{
	struct device_node *fw_node;
	struct rpi_firmware *fw;
	int err;

	fw_node = of_find_compatible_node(NULL, NULL,
					  "raspberrypi,bcm2835-firmware");
	if (!fw_node) {
		dev_err(&pdev->dev, "Missing firmware node\n");
		return -ENOENT;
	}

	fw = rpi_firmware_get(fw_node);
	of_node_put(fw_node);
	if (!fw)
		return -EPROBE_DEFER;

	platform_set_drvdata(pdev, fw);

	err = vchiq_platform_init(pdev, &g_state);
	if (err != 0)
		goto failed_platform_init;

	err = alloc_chrdev_region(&vchiq_devid, VCHIQ_MINOR, 1, DEVICE_NAME);
	if (err != 0) {
		vchiq_log_error(vchiq_arm_log_level,
			"Unable to allocate device number");
		goto failed_platform_init;
	}
	cdev_init(&vchiq_cdev, &vchiq_fops);
	vchiq_cdev.owner = THIS_MODULE;
	err = cdev_add(&vchiq_cdev, vchiq_devid, 1);
	if (err != 0) {
		vchiq_log_error(vchiq_arm_log_level,
			"Unable to register device");
		goto failed_cdev_add;
	}

	/* create sysfs entries */
	vchiq_class = class_create(THIS_MODULE, DEVICE_NAME);
	err = PTR_ERR(vchiq_class);
	if (IS_ERR(vchiq_class))
		goto failed_class_create;

	vchiq_dev = device_create(vchiq_class, NULL,
		vchiq_devid, NULL, "vchiq");
	err = PTR_ERR(vchiq_dev);
	if (IS_ERR(vchiq_dev))
		goto failed_device_create;

	/* create debugfs entries */
	vchiq_debugfs_init();

	vchiq_log_info(vchiq_arm_log_level,
		"vchiq: initialised - version %d (min %d), device %d.%d",
		VCHIQ_VERSION, VCHIQ_VERSION_MIN,
		MAJOR(vchiq_devid), MINOR(vchiq_devid));

	vcsm_cma = vchiq_register_child(pdev, "vcsm-cma");
	if (IS_ERR(vcsm_cma))
		vcsm_cma = NULL;
	bcm2835_camera = vchiq_register_child(pdev, "bcm2835-camera");
	if (IS_ERR(bcm2835_camera))
		bcm2835_camera = NULL;
	bcm2835_codec = vchiq_register_child(pdev, "bcm2835-codec");
	if (IS_ERR(bcm2835_codec))
		bcm2835_codec = NULL;

	return 0;

failed_device_create:
	class_destroy(vchiq_class);
failed_class_create:
	cdev_del(&vchiq_cdev);
failed_cdev_add:
	unregister_chrdev_region(vchiq_devid, 1);
failed_platform_init:
	vchiq_log_warning(vchiq_arm_log_level, "could not load vchiq");
	return err;
}