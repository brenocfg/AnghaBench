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
struct bm2835_mmal_dev {int /*<<< orphan*/  camera_use_count; int /*<<< orphan*/  v4l2_dev; TYPE_1__** component; int /*<<< orphan*/  instance; } ;
typedef  int /*<<< orphan*/  i ;
struct TYPE_2__ {int /*<<< orphan*/  control; } ;

/* Variables and functions */
 size_t COMP_CAMERA ; 
 int EINVAL ; 
 int /*<<< orphan*/  MMAL_PARAMETER_CAMERA_NUM ; 
 int /*<<< orphan*/  bcm2835_v4l2_debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,...) ; 
 int vchiq_mmal_component_disable (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vchiq_mmal_port_parameter_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int*,int) ; 

__attribute__((used)) static int disable_camera(struct bm2835_mmal_dev *dev)
{
	int ret;

	if (!dev->camera_use_count) {
		v4l2_err(&dev->v4l2_dev,
			 "Disabled the camera when already disabled\n");
		return -EINVAL;
	}
	dev->camera_use_count--;
	if (!dev->camera_use_count) {
		unsigned int i = 0xFFFFFFFF;

		v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
			 "Disabling camera\n");
		ret =
		    vchiq_mmal_component_disable(
				dev->instance,
				dev->component[COMP_CAMERA]);
		if (ret < 0) {
			v4l2_err(&dev->v4l2_dev,
				 "Failed disabling camera, ret %d\n", ret);
			return -EINVAL;
		}
		vchiq_mmal_port_parameter_set(
			dev->instance,
			&dev->component[COMP_CAMERA]->control,
			MMAL_PARAMETER_CAMERA_NUM, &i,
			sizeof(i));
	}
	v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
		 "Camera refcount now %d\n", dev->camera_use_count);
	return 0;
}