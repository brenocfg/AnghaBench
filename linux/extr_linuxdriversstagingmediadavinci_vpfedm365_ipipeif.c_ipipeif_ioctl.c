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
struct v4l2_subdev {int dummy; } ;
struct ipipeif_params {int dummy; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
#define  VIDIOC_VPFE_IPIPEIF_G_CONFIG 129 
#define  VIDIOC_VPFE_IPIPEIF_S_CONFIG 128 
 int ipipeif_get_config (struct v4l2_subdev*,void*) ; 
 int ipipeif_set_config (struct v4l2_subdev*,struct ipipeif_params*) ; 

__attribute__((used)) static long ipipeif_ioctl(struct v4l2_subdev *sd,
			  unsigned int cmd, void *arg)
{
	struct ipipeif_params *config = arg;
	int ret = -ENOIOCTLCMD;

	switch (cmd) {
	case VIDIOC_VPFE_IPIPEIF_S_CONFIG:
		ret = ipipeif_set_config(sd, config);
		break;

	case VIDIOC_VPFE_IPIPEIF_G_CONFIG:
		ret = ipipeif_get_config(sd, arg);
		break;
	}
	return ret;
}