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
typedef  int /*<<< orphan*/  u32 ;
struct vchiq_mmal_port {int dummy; } ;
struct v4l2_ctrl {int val; } ;
struct bm2835_mmal_v4l2_ctrl {int /*<<< orphan*/  mmal_id; } ;
struct TYPE_4__ {int encode_bitrate_mode; } ;
struct bm2835_mmal_dev {int /*<<< orphan*/  instance; TYPE_2__ capture; TYPE_1__** component; } ;
typedef  int /*<<< orphan*/  bitrate_mode ;
struct TYPE_3__ {struct vchiq_mmal_port* output; } ;

/* Variables and functions */
 size_t COMP_VIDEO_ENCODE ; 
 int /*<<< orphan*/  MMAL_VIDEO_RATECONTROL_CONSTANT ; 
 int /*<<< orphan*/  MMAL_VIDEO_RATECONTROL_VARIABLE ; 
#define  V4L2_MPEG_VIDEO_BITRATE_MODE_CBR 129 
#define  V4L2_MPEG_VIDEO_BITRATE_MODE_VBR 128 
 int /*<<< orphan*/  vchiq_mmal_port_parameter_set (int /*<<< orphan*/ ,struct vchiq_mmal_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ctrl_set_bitrate_mode(struct bm2835_mmal_dev *dev,
				 struct v4l2_ctrl *ctrl,
				 const struct bm2835_mmal_v4l2_ctrl *mmal_ctrl)
{
	u32 bitrate_mode;
	struct vchiq_mmal_port *encoder_out;

	encoder_out = &dev->component[COMP_VIDEO_ENCODE]->output[0];

	dev->capture.encode_bitrate_mode = ctrl->val;
	switch (ctrl->val) {
	default:
	case V4L2_MPEG_VIDEO_BITRATE_MODE_VBR:
		bitrate_mode = MMAL_VIDEO_RATECONTROL_VARIABLE;
		break;
	case V4L2_MPEG_VIDEO_BITRATE_MODE_CBR:
		bitrate_mode = MMAL_VIDEO_RATECONTROL_CONSTANT;
		break;
	}

	vchiq_mmal_port_parameter_set(dev->instance, encoder_out,
				      mmal_ctrl->mmal_id,
					     &bitrate_mode,
					     sizeof(bitrate_mode));
	return 0;
}