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
struct v4l2_ctrl {int id; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_BRIGHTNESS 131 
#define  V4L2_CID_CONTRAST 130 
#define  V4L2_CID_HUE 129 
#define  V4L2_CID_SATURATION 128 

__attribute__((used)) static int skeleton_s_ctrl(struct v4l2_ctrl *ctrl)
{
	/*struct skeleton *skel =
		container_of(ctrl->handler, struct skeleton, ctrl_handler);*/

	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		/* TODO: set brightness to ctrl->val */
		break;
	case V4L2_CID_CONTRAST:
		/* TODO: set contrast to ctrl->val */
		break;
	case V4L2_CID_SATURATION:
		/* TODO: set saturation to ctrl->val */
		break;
	case V4L2_CID_HUE:
		/* TODO: set hue to ctrl->val */
		break;
	default:
		return -EINVAL;
	}
	return 0;
}