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
struct spmi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  usid; struct spmi_controller* ctrl; } ;
struct spmi_controller {int /*<<< orphan*/  nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_add (int /*<<< orphan*/ *) ; 

int spmi_device_add(struct spmi_device *sdev)
{
	struct spmi_controller *ctrl = sdev->ctrl;
	int err;

	dev_set_name(&sdev->dev, "%d-%02x", ctrl->nr, sdev->usid);

	err = device_add(&sdev->dev);
	if (err < 0) {
		dev_err(&sdev->dev, "Can't add %s, status %d\n",
			dev_name(&sdev->dev), err);
		goto err_device_add;
	}

	dev_dbg(&sdev->dev, "device %s registered\n", dev_name(&sdev->dev));

err_device_add:
	return err;
}