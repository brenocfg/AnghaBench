#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  entity; } ;
struct TYPE_5__ {int /*<<< orphan*/  entity; } ;
struct TYPE_6__ {TYPE_1__ video_dev; struct vpfe_device* vpfe_dev; } ;
struct vpfe_ipipeif_device {TYPE_3__ subdev; TYPE_2__ video_in; } ;
struct vpfe_device {int dummy; } ;
struct v4l2_device {int dummy; } ;

/* Variables and functions */
 int media_create_pad_link (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct vpfe_device* to_vpfe_device (struct vpfe_ipipeif_device*) ; 
 int v4l2_device_register_subdev (struct v4l2_device*,TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (TYPE_3__*) ; 
 int vpfe_video_register (TYPE_2__*,struct v4l2_device*) ; 

int
vpfe_ipipeif_register_entities(struct vpfe_ipipeif_device *ipipeif,
			       struct v4l2_device *vdev)
{
	struct vpfe_device *vpfe_dev = to_vpfe_device(ipipeif);
	unsigned int flags;
	int ret;

	/* Register the subdev */
	ret = v4l2_device_register_subdev(vdev, &ipipeif->subdev);
	if (ret < 0)
		return ret;

	ret = vpfe_video_register(&ipipeif->video_in, vdev);
	if (ret) {
		pr_err("Failed to register ipipeif video-in device\n");
		goto fail;
	}
	ipipeif->video_in.vpfe_dev = vpfe_dev;

	flags = 0;
	ret = media_create_pad_link(&ipipeif->video_in.video_dev.entity, 0,
					&ipipeif->subdev.entity, 0, flags);
	if (ret < 0)
		goto fail;

	return 0;
fail:
	v4l2_device_unregister_subdev(&ipipeif->subdev);

	return ret;
}