#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  entity; } ;
struct TYPE_6__ {int /*<<< orphan*/  entity; } ;
struct TYPE_7__ {TYPE_1__ video_dev; struct vpfe_device* vpfe_dev; } ;
struct vpfe_isif_device {TYPE_4__ subdev; TYPE_2__ video_out; } ;
struct vpfe_device {int dummy; } ;
struct v4l2_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  isif_restore_defaults (struct vpfe_isif_device*) ; 
 int media_create_pad_link (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct vpfe_device* to_vpfe_device (struct vpfe_isif_device*) ; 
 int v4l2_device_register_subdev (struct v4l2_device*,TYPE_4__*) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (TYPE_4__*) ; 
 int vpfe_video_register (TYPE_2__*,struct v4l2_device*) ; 
 int /*<<< orphan*/  vpfe_video_unregister (TYPE_2__*) ; 

int vpfe_isif_register_entities(struct vpfe_isif_device *isif,
			    struct v4l2_device *vdev)
{
	struct vpfe_device *vpfe_dev = to_vpfe_device(isif);
	unsigned int flags;
	int ret;

	/* Register the subdev */
	ret = v4l2_device_register_subdev(vdev, &isif->subdev);
	if (ret < 0)
		return ret;

	isif_restore_defaults(isif);
	ret = vpfe_video_register(&isif->video_out, vdev);
	if (ret) {
		pr_err("Failed to register isif video out device\n");
		goto out_video_register;
	}
	isif->video_out.vpfe_dev = vpfe_dev;
	flags = 0;
	/* connect isif to video node */
	ret = media_create_pad_link(&isif->subdev.entity, 1,
				       &isif->video_out.video_dev.entity,
				       0, flags);
	if (ret < 0)
		goto out_create_link;
	return 0;
out_create_link:
	vpfe_video_unregister(&isif->video_out);
out_video_register:
	v4l2_device_unregister_subdev(&isif->subdev);
	return ret;
}