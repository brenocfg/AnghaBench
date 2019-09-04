#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct device* parent; } ;
struct usb_device {TYPE_1__ dev; } ;
struct p54u_priv {struct usb_device* udev; struct firmware const* fw; int /*<<< orphan*/  fw_wait_load; } ;
struct firmware {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_release_driver (TYPE_1__*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 
 int p54u_start_ops (struct p54u_priv*) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 

__attribute__((used)) static void p54u_load_firmware_cb(const struct firmware *firmware,
				  void *context)
{
	struct p54u_priv *priv = context;
	struct usb_device *udev = priv->udev;
	int err;

	complete(&priv->fw_wait_load);
	if (firmware) {
		priv->fw = firmware;
		err = p54u_start_ops(priv);
	} else {
		err = -ENOENT;
		dev_err(&udev->dev, "Firmware not found.\n");
	}

	if (err) {
		struct device *parent = priv->udev->dev.parent;

		dev_err(&udev->dev, "failed to initialize device (%d)\n", err);

		if (parent)
			device_lock(parent);

		device_release_driver(&udev->dev);
		/*
		 * At this point p54u_disconnect has already freed
		 * the "priv" context. Do not use it anymore!
		 */
		priv = NULL;

		if (parent)
			device_unlock(parent);
	}

	usb_put_dev(udev);
}