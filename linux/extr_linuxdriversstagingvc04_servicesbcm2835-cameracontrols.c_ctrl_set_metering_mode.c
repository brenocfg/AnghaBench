#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32_value ;
typedef  int /*<<< orphan*/  u32 ;
struct vchiq_mmal_port {int dummy; } ;
struct v4l2_ctrl {int val; } ;
struct bm2835_mmal_v4l2_ctrl {int /*<<< orphan*/  mmal_id; } ;
struct bm2835_mmal_dev {scalar_t__ scene_mode; int /*<<< orphan*/  instance; TYPE_1__** component; int /*<<< orphan*/  metering_mode; } ;
struct TYPE_2__ {struct vchiq_mmal_port control; } ;

/* Variables and functions */
 size_t COMP_CAMERA ; 
 int /*<<< orphan*/  MMAL_PARAM_EXPOSUREMETERINGMODE_AVERAGE ; 
 int /*<<< orphan*/  MMAL_PARAM_EXPOSUREMETERINGMODE_BACKLIT ; 
 int /*<<< orphan*/  MMAL_PARAM_EXPOSUREMETERINGMODE_SPOT ; 
#define  V4L2_EXPOSURE_METERING_AVERAGE 130 
#define  V4L2_EXPOSURE_METERING_CENTER_WEIGHTED 129 
#define  V4L2_EXPOSURE_METERING_SPOT 128 
 scalar_t__ V4L2_SCENE_MODE_NONE ; 
 int vchiq_mmal_port_parameter_set (int /*<<< orphan*/ ,struct vchiq_mmal_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ctrl_set_metering_mode(struct bm2835_mmal_dev *dev,
				  struct v4l2_ctrl *ctrl,
				  const struct bm2835_mmal_v4l2_ctrl *mmal_ctrl)
{
	switch (ctrl->val) {
	case V4L2_EXPOSURE_METERING_AVERAGE:
		dev->metering_mode = MMAL_PARAM_EXPOSUREMETERINGMODE_AVERAGE;
		break;

	case V4L2_EXPOSURE_METERING_CENTER_WEIGHTED:
		dev->metering_mode = MMAL_PARAM_EXPOSUREMETERINGMODE_BACKLIT;
		break;

	case V4L2_EXPOSURE_METERING_SPOT:
		dev->metering_mode = MMAL_PARAM_EXPOSUREMETERINGMODE_SPOT;
		break;

	/* todo matrix weighting not added to Linux API till 3.9
	 * case V4L2_EXPOSURE_METERING_MATRIX:
	 *	dev->metering_mode = MMAL_PARAM_EXPOSUREMETERINGMODE_MATRIX;
	 *	break;
	 */
	}

	if (dev->scene_mode == V4L2_SCENE_MODE_NONE) {
		struct vchiq_mmal_port *control;
		u32 u32_value = dev->metering_mode;

		control = &dev->component[COMP_CAMERA]->control;

		return vchiq_mmal_port_parameter_set(dev->instance, control,
					     mmal_ctrl->mmal_id,
					     &u32_value, sizeof(u32_value));
	} else {
		return 0;
	}
}