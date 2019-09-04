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

/* Variables and functions */
 long ENOIOCTLCMD ; 
#define  VIDIOC_VPFE_ISIF_G_RAW_PARAMS 129 
#define  VIDIOC_VPFE_ISIF_S_RAW_PARAMS 128 
 long isif_get_params (struct v4l2_subdev*,void*) ; 
 long isif_set_params (struct v4l2_subdev*,void*) ; 

__attribute__((used)) static long isif_ioctl(struct v4l2_subdev *sd, unsigned int cmd, void *arg)
{
	switch (cmd) {
	case VIDIOC_VPFE_ISIF_S_RAW_PARAMS:
		return isif_set_params(sd, arg);

	case VIDIOC_VPFE_ISIF_G_RAW_PARAMS:
		return isif_get_params(sd, arg);

	default:
		return -ENOIOCTLCMD;
	}
}