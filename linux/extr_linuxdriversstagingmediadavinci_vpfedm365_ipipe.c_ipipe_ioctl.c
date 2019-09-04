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
#define  VIDIOC_VPFE_IPIPE_G_CONFIG 129 
#define  VIDIOC_VPFE_IPIPE_S_CONFIG 128 
 long ipipe_g_config (struct v4l2_subdev*,void*) ; 
 long ipipe_s_config (struct v4l2_subdev*,void*) ; 

__attribute__((used)) static long ipipe_ioctl(struct v4l2_subdev *sd, unsigned int cmd, void *arg)
{
	switch (cmd) {
	case VIDIOC_VPFE_IPIPE_S_CONFIG:
		return ipipe_s_config(sd, arg);

	case VIDIOC_VPFE_IPIPE_G_CONFIG:
		return ipipe_g_config(sd, arg);

	default:
		return -ENOIOCTLCMD;
	}
}