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
struct TYPE_2__ {scalar_t__ encode_component; int /*<<< orphan*/  camera_port; } ;
struct bm2835_mmal_dev {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  ctrl_handler; scalar_t__* component; int /*<<< orphan*/  instance; TYPE_1__ capture; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 size_t COMP_CAMERA ; 
 size_t COMP_IMAGE_ENCODE ; 
 size_t COMP_PREVIEW ; 
 size_t COMP_VIDEO_ENCODE ; 
 int /*<<< orphan*/  bcm2835_v4l2_debug ; 
 int /*<<< orphan*/  kfree (struct bm2835_mmal_dev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_mmal_component_disable (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vchiq_mmal_component_finalise (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vchiq_mmal_port_connect_tunnel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_device_node_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcm2835_cleanup_instance(struct bm2835_mmal_dev *dev)
{
	if (!dev)
		return;

	v4l2_info(&dev->v4l2_dev, "unregistering %s\n",
		  video_device_node_name(&dev->vdev));

	video_unregister_device(&dev->vdev);

	if (dev->capture.encode_component) {
		v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
			 "mmal_exit - disconnect tunnel\n");
		vchiq_mmal_port_connect_tunnel(dev->instance,
					       dev->capture.camera_port, NULL);
		vchiq_mmal_component_disable(dev->instance,
					     dev->capture.encode_component);
	}
	vchiq_mmal_component_disable(dev->instance,
				     dev->component[COMP_CAMERA]);

	vchiq_mmal_component_finalise(dev->instance,
				      dev->component[COMP_VIDEO_ENCODE]);

	vchiq_mmal_component_finalise(dev->instance,
				      dev->component[COMP_IMAGE_ENCODE]);

	vchiq_mmal_component_finalise(dev->instance,
				      dev->component[COMP_PREVIEW]);

	vchiq_mmal_component_finalise(dev->instance,
				      dev->component[COMP_CAMERA]);

	v4l2_ctrl_handler_free(&dev->ctrl_handler);

	v4l2_device_unregister(&dev->v4l2_dev);

	kfree(dev);
}