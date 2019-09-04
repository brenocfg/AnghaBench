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
struct vpfe_ipipeif_device {int dummy; } ;
struct vpfe_device {int dummy; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int ipipeif_hw_setup (struct v4l2_subdev*) ; 
 struct vpfe_device* to_vpfe_device (struct vpfe_ipipeif_device*) ; 
 struct vpfe_ipipeif_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  vpfe_ipipeif_enable (struct vpfe_device*) ; 

__attribute__((used)) static int ipipeif_set_stream(struct v4l2_subdev *sd, int enable)
{
	struct vpfe_ipipeif_device *ipipeif = v4l2_get_subdevdata(sd);
	struct vpfe_device *vpfe_dev = to_vpfe_device(ipipeif);
	int ret = 0;

	if (!enable)
		return ret;

	ret = ipipeif_hw_setup(sd);
	if (!ret)
		vpfe_ipipeif_enable(vpfe_dev);

	return ret;
}