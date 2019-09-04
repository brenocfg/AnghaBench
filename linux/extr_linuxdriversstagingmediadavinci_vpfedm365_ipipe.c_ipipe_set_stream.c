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
struct vpfe_ipipe_device {scalar_t__ input; scalar_t__ output; } ;
struct vpfe_device {int dummy; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IPIPE_INPUT_NONE ; 
 scalar_t__ IPIPE_OUTPUT_NONE ; 
 scalar_t__ config_ipipe_hw (struct vpfe_ipipe_device*) ; 
 struct vpfe_device* to_vpfe_device (struct vpfe_ipipe_device*) ; 
 struct vpfe_ipipe_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  vpfe_ipipe_enable (struct vpfe_device*,int) ; 

__attribute__((used)) static int ipipe_set_stream(struct v4l2_subdev *sd, int enable)
{
	struct vpfe_ipipe_device *ipipe = v4l2_get_subdevdata(sd);
	struct vpfe_device *vpfe_dev = to_vpfe_device(ipipe);

	if (enable && ipipe->input != IPIPE_INPUT_NONE &&
		ipipe->output != IPIPE_OUTPUT_NONE) {
		if (config_ipipe_hw(ipipe) < 0)
			return -EINVAL;
	}

	vpfe_ipipe_enable(vpfe_dev, enable);

	return 0;
}