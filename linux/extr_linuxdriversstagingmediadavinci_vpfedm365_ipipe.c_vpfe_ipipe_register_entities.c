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
struct vpfe_ipipe_device {int /*<<< orphan*/  subdev; } ;
struct v4l2_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*) ; 
 int v4l2_device_register_subdev (struct v4l2_device*,int /*<<< orphan*/ *) ; 

int
vpfe_ipipe_register_entities(struct vpfe_ipipe_device *ipipe,
				 struct v4l2_device *vdev)
{
	int ret;

	/* Register the subdev */
	ret = v4l2_device_register_subdev(vdev, &ipipe->subdev);
	if (ret) {
		pr_err("Failed to register ipipe as v4l2 subdevice\n");
		return ret;
	}

	return ret;
}