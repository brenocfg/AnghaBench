#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  entity; } ;
struct TYPE_9__ {int /*<<< orphan*/  entity; } ;
struct TYPE_13__ {TYPE_1__ video_dev; struct vpfe_device* vpfe_dev; } ;
struct TYPE_12__ {TYPE_7__ subdev; TYPE_5__ video_out; } ;
struct TYPE_11__ {TYPE_7__ subdev; TYPE_5__ video_out; } ;
struct TYPE_10__ {TYPE_7__ subdev; } ;
struct vpfe_resizer_device {TYPE_4__ resizer_b; TYPE_3__ resizer_a; TYPE_2__ crop_resizer; } ;
struct vpfe_device {int dummy; } ;
struct v4l2_device {int dummy; } ;

/* Variables and functions */
 int media_create_pad_link (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct vpfe_device* to_vpfe_device (struct vpfe_resizer_device*) ; 
 int v4l2_device_register_subdev (struct v4l2_device*,TYPE_7__*) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (TYPE_7__*) ; 
 int vpfe_video_register (TYPE_5__*,struct v4l2_device*) ; 
 int /*<<< orphan*/  vpfe_video_unregister (TYPE_5__*) ; 

int vpfe_resizer_register_entities(struct vpfe_resizer_device *resizer,
				   struct v4l2_device *vdev)
{
	struct vpfe_device *vpfe_dev = to_vpfe_device(resizer);
	unsigned int flags = 0;
	int ret;

	/* Register the crop resizer subdev */
	ret = v4l2_device_register_subdev(vdev, &resizer->crop_resizer.subdev);
	if (ret < 0) {
		pr_err("Failed to register crop resizer as v4l2-subdev\n");
		return ret;
	}
	/* Register Resizer-A subdev */
	ret = v4l2_device_register_subdev(vdev, &resizer->resizer_a.subdev);
	if (ret < 0) {
		pr_err("Failed to register resizer-a as v4l2-subdev\n");
		return ret;
	}
	/* Register Resizer-B subdev */
	ret = v4l2_device_register_subdev(vdev, &resizer->resizer_b.subdev);
	if (ret < 0) {
		pr_err("Failed to register resizer-b as v4l2-subdev\n");
		return ret;
	}
	/* Register video-out device for resizer-a */
	ret = vpfe_video_register(&resizer->resizer_a.video_out, vdev);
	if (ret) {
		pr_err("Failed to register RSZ-A video-out device\n");
		goto out_video_out2_register;
	}
	resizer->resizer_a.video_out.vpfe_dev = vpfe_dev;

	/* Register video-out device for resizer-b */
	ret = vpfe_video_register(&resizer->resizer_b.video_out, vdev);
	if (ret) {
		pr_err("Failed to register RSZ-B video-out device\n");
		goto out_video_out2_register;
	}
	resizer->resizer_b.video_out.vpfe_dev = vpfe_dev;

	/* create link between Resizer Crop----> Resizer A*/
	ret = media_create_pad_link(&resizer->crop_resizer.subdev.entity, 1,
				&resizer->resizer_a.subdev.entity,
				0, flags);
	if (ret < 0)
		goto out_create_link;

	/* create link between Resizer Crop----> Resizer B*/
	ret = media_create_pad_link(&resizer->crop_resizer.subdev.entity, 2,
				&resizer->resizer_b.subdev.entity,
				0, flags);
	if (ret < 0)
		goto out_create_link;

	/* create link between Resizer A ----> video out */
	ret = media_create_pad_link(&resizer->resizer_a.subdev.entity, 1,
		&resizer->resizer_a.video_out.video_dev.entity, 0, flags);
	if (ret < 0)
		goto out_create_link;

	/* create link between Resizer B ----> video out */
	ret = media_create_pad_link(&resizer->resizer_b.subdev.entity, 1,
		&resizer->resizer_b.video_out.video_dev.entity, 0, flags);
	if (ret < 0)
		goto out_create_link;

	return 0;

out_create_link:
	vpfe_video_unregister(&resizer->resizer_b.video_out);
out_video_out2_register:
	vpfe_video_unregister(&resizer->resizer_a.video_out);
	v4l2_device_unregister_subdev(&resizer->crop_resizer.subdev);
	v4l2_device_unregister_subdev(&resizer->resizer_a.subdev);
	v4l2_device_unregister_subdev(&resizer->resizer_b.subdev);
	media_entity_cleanup(&resizer->crop_resizer.subdev.entity);
	media_entity_cleanup(&resizer->resizer_a.subdev.entity);
	media_entity_cleanup(&resizer->resizer_b.subdev.entity);
	return ret;
}