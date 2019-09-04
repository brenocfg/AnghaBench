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
struct v4l2_ctrl {int /*<<< orphan*/  val; } ;
struct bm2835_mmal_v4l2_ctrl {int /*<<< orphan*/  mmal_id; } ;
struct bm2835_mmal_dev {int /*<<< orphan*/  instance; TYPE_1__** component; } ;
struct TYPE_2__ {struct vchiq_mmal_port* output; } ;

/* Variables and functions */
 size_t COMP_IMAGE_ENCODE ; 
 int vchiq_mmal_port_parameter_set (int /*<<< orphan*/ ,struct vchiq_mmal_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ctrl_set_image_encode_output(struct bm2835_mmal_dev *dev,
					struct v4l2_ctrl *ctrl,
					const struct bm2835_mmal_v4l2_ctrl *mmal_ctrl)
{
	u32 u32_value;
	struct vchiq_mmal_port *jpeg_out;

	jpeg_out = &dev->component[COMP_IMAGE_ENCODE]->output[0];

	u32_value = ctrl->val;

	return vchiq_mmal_port_parameter_set(dev->instance, jpeg_out,
					     mmal_ctrl->mmal_id,
					     &u32_value, sizeof(u32_value));
}