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
struct vchiq_mmal_port {int dummy; } ;
struct v4l2_ctrl {int /*<<< orphan*/  val; } ;
struct bm2835_mmal_v4l2_ctrl {int /*<<< orphan*/  mmal_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  encode_bitrate; } ;
struct bm2835_mmal_dev {int /*<<< orphan*/  instance; TYPE_2__** component; TYPE_1__ capture; } ;
struct TYPE_4__ {struct vchiq_mmal_port* output; } ;

/* Variables and functions */
 size_t COMP_VIDEO_ENCODE ; 
 int vchiq_mmal_port_parameter_set (int /*<<< orphan*/ ,struct vchiq_mmal_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ctrl_set_bitrate(struct bm2835_mmal_dev *dev,
			    struct v4l2_ctrl *ctrl,
			    const struct bm2835_mmal_v4l2_ctrl *mmal_ctrl)
{
	int ret;
	struct vchiq_mmal_port *encoder_out;

	dev->capture.encode_bitrate = ctrl->val;

	encoder_out = &dev->component[COMP_VIDEO_ENCODE]->output[0];

	ret = vchiq_mmal_port_parameter_set(dev->instance, encoder_out,
					    mmal_ctrl->mmal_id,
					    &ctrl->val, sizeof(ctrl->val));
	ret = 0;
	return ret;
}