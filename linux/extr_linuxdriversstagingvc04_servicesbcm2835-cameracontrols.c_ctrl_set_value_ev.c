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
struct vchiq_mmal_port {int dummy; } ;
struct v4l2_ctrl {int val; } ;
struct bm2835_mmal_v4l2_ctrl {int /*<<< orphan*/  mmal_id; } ;
struct bm2835_mmal_dev {int /*<<< orphan*/  instance; TYPE_1__** component; } ;
typedef  int /*<<< orphan*/  s32_value ;
typedef  int s32 ;
struct TYPE_2__ {struct vchiq_mmal_port control; } ;

/* Variables and functions */
 size_t COMP_CAMERA ; 
 int vchiq_mmal_port_parameter_set (int /*<<< orphan*/ ,struct vchiq_mmal_port*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int ctrl_set_value_ev(struct bm2835_mmal_dev *dev,
			     struct v4l2_ctrl *ctrl,
			     const struct bm2835_mmal_v4l2_ctrl *mmal_ctrl)
{
	s32 s32_value;
	struct vchiq_mmal_port *control;

	control = &dev->component[COMP_CAMERA]->control;

	s32_value = (ctrl->val - 12) * 2;	/* Convert from index to 1/6ths */

	return vchiq_mmal_port_parameter_set(dev->instance, control,
					     mmal_ctrl->mmal_id,
					     &s32_value, sizeof(s32_value));
}