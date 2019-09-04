#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  entity; } ;
struct vpfe_video_device {TYPE_1__ video_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 scalar_t__ video_is_registered (TYPE_1__*) ; 
 int /*<<< orphan*/  video_unregister_device (TYPE_1__*) ; 

void vpfe_video_unregister(struct vpfe_video_device *video)
{
	if (video_is_registered(&video->video_dev)) {
		video_unregister_device(&video->video_dev);
		media_entity_cleanup(&video->video_dev.entity);
	}
}