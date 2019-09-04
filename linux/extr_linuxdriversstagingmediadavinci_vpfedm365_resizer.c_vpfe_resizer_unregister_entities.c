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
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  entity; } ;
struct TYPE_7__ {TYPE_4__ subdev; int /*<<< orphan*/  video_out; } ;
struct TYPE_6__ {TYPE_4__ subdev; int /*<<< orphan*/  video_out; } ;
struct TYPE_5__ {TYPE_4__ subdev; } ;
struct vpfe_resizer_device {TYPE_3__ resizer_b; TYPE_2__ resizer_a; TYPE_1__ crop_resizer; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (TYPE_4__*) ; 
 int /*<<< orphan*/  vpfe_video_unregister (int /*<<< orphan*/ *) ; 

void vpfe_resizer_unregister_entities(struct vpfe_resizer_device *vpfe_rsz)
{
	/* unregister video devices */
	vpfe_video_unregister(&vpfe_rsz->resizer_a.video_out);
	vpfe_video_unregister(&vpfe_rsz->resizer_b.video_out);

	/* unregister subdev */
	v4l2_device_unregister_subdev(&vpfe_rsz->crop_resizer.subdev);
	v4l2_device_unregister_subdev(&vpfe_rsz->resizer_a.subdev);
	v4l2_device_unregister_subdev(&vpfe_rsz->resizer_b.subdev);
	/* cleanup entity */
	media_entity_cleanup(&vpfe_rsz->crop_resizer.subdev.entity);
	media_entity_cleanup(&vpfe_rsz->resizer_a.subdev.entity);
	media_entity_cleanup(&vpfe_rsz->resizer_b.subdev.entity);
}