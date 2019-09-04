#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vpfe_rsz_config {int /*<<< orphan*/  config; } ;
struct v4l2_subdev {TYPE_1__* v4l2_dev; } ;
struct TYPE_4__ {struct v4l2_subdev subdev; } ;
struct vpfe_resizer_device {TYPE_2__ crop_resizer; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device* dev; } ;

/* Variables and functions */
 long EINVAL ; 
 int ENOIOCTLCMD ; 
#define  VIDIOC_VPFE_RSZ_G_CONFIG 129 
#define  VIDIOC_VPFE_RSZ_S_CONFIG 128 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int resizer_get_configuration (struct vpfe_resizer_device*,struct vpfe_rsz_config*) ; 
 int resizer_set_configuration (struct vpfe_resizer_device*,struct vpfe_rsz_config*) ; 
 struct vpfe_resizer_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static long resizer_ioctl(struct v4l2_subdev *sd, unsigned int cmd, void *arg)
{
	struct vpfe_resizer_device *resizer = v4l2_get_subdevdata(sd);
	struct device *dev = resizer->crop_resizer.subdev.v4l2_dev->dev;
	struct vpfe_rsz_config *user_config;
	int ret = -ENOIOCTLCMD;

	if (&resizer->crop_resizer.subdev != sd)
		return ret;

	switch (cmd) {
	case VIDIOC_VPFE_RSZ_S_CONFIG:
		user_config = arg;
		ret = resizer_set_configuration(resizer, user_config);
		break;

	case VIDIOC_VPFE_RSZ_G_CONFIG:
		user_config = arg;
		if (!user_config->config) {
			dev_err(dev, "error in VIDIOC_VPFE_RSZ_G_CONFIG\n");
			return -EINVAL;
		}
		ret = resizer_get_configuration(resizer, user_config);
		break;
	}
	return ret;
}