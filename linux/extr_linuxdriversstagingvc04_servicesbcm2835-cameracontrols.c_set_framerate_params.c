#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int num; int den; } ;
struct TYPE_8__ {int num; int den; } ;
struct mmal_parameter_fps_range {TYPE_4__ fps_high; TYPE_3__ fps_low; } ;
struct TYPE_6__ {int denominator; int numerator; } ;
struct TYPE_7__ {TYPE_1__ timeperframe; } ;
struct bm2835_mmal_dev {scalar_t__ exposure_mode_active; int /*<<< orphan*/  v4l2_dev; TYPE_5__** component; int /*<<< orphan*/  instance; TYPE_2__ capture; scalar_t__ exp_auto_priority; } ;
typedef  int /*<<< orphan*/  fps_range ;
struct TYPE_10__ {int /*<<< orphan*/ * output; } ;

/* Variables and functions */
 size_t CAM_PORT_CAPTURE ; 
 size_t CAM_PORT_PREVIEW ; 
 size_t CAM_PORT_VIDEO ; 
 size_t COMP_CAMERA ; 
 int /*<<< orphan*/  MMAL_PARAMETER_FPS_RANGE ; 
 scalar_t__ MMAL_PARAM_EXPOSUREMODE_OFF ; 
 int /*<<< orphan*/  bcm2835_v4l2_debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,...) ; 
 int vchiq_mmal_port_parameter_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mmal_parameter_fps_range*,int) ; 

int set_framerate_params(struct bm2835_mmal_dev *dev)
{
	struct mmal_parameter_fps_range fps_range;
	int ret;

	if ((dev->exposure_mode_active != MMAL_PARAM_EXPOSUREMODE_OFF) &&
	    (dev->exp_auto_priority)) {
		/* Variable FPS. Define min FPS as 1fps.
		 * Max as max defined FPS.
		 */
		fps_range.fps_low.num = 1;
		fps_range.fps_low.den = 1;
		fps_range.fps_high.num = dev->capture.timeperframe.denominator;
		fps_range.fps_high.den = dev->capture.timeperframe.numerator;
	} else {
		/* Fixed FPS - set min and max to be the same */
		fps_range.fps_low.num = fps_range.fps_high.num =
			dev->capture.timeperframe.denominator;
		fps_range.fps_low.den = fps_range.fps_high.den =
			dev->capture.timeperframe.numerator;
	}

	v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
		 "Set fps range to %d/%d to %d/%d\n",
		 fps_range.fps_low.num,
		 fps_range.fps_low.den,
		 fps_range.fps_high.num,
		 fps_range.fps_high.den);

	ret = vchiq_mmal_port_parameter_set(dev->instance,
					    &dev->component[COMP_CAMERA]->output[CAM_PORT_PREVIEW],
					    MMAL_PARAMETER_FPS_RANGE,
					    &fps_range, sizeof(fps_range));
	ret += vchiq_mmal_port_parameter_set(dev->instance,
					     &dev->component[COMP_CAMERA]->output[CAM_PORT_VIDEO],
					     MMAL_PARAMETER_FPS_RANGE,
					     &fps_range, sizeof(fps_range));
	ret += vchiq_mmal_port_parameter_set(dev->instance,
					     &dev->component[COMP_CAMERA]->output[CAM_PORT_CAPTURE],
					     MMAL_PARAMETER_FPS_RANGE,
					     &fps_range, sizeof(fps_range));
	if (ret)
		v4l2_dbg(0, bcm2835_v4l2_debug, &dev->v4l2_dev,
			 "Failed to set fps ret %d\n", ret);

	return ret;
}