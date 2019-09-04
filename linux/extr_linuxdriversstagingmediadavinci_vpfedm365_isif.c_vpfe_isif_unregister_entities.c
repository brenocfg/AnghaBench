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
struct TYPE_2__ {int /*<<< orphan*/  entity; } ;
struct vpfe_isif_device {TYPE_1__ subdev; int /*<<< orphan*/  video_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (TYPE_1__*) ; 
 int /*<<< orphan*/  vpfe_video_unregister (int /*<<< orphan*/ *) ; 

void vpfe_isif_unregister_entities(struct vpfe_isif_device *isif)
{
	vpfe_video_unregister(&isif->video_out);
	/* unregister subdev */
	v4l2_device_unregister_subdev(&isif->subdev);
	/* cleanup entity */
	media_entity_cleanup(&isif->subdev.entity);
}