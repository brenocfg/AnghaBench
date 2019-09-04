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
struct iss_video {int /*<<< orphan*/  mutex; int /*<<< orphan*/  stream_lock; TYPE_1__ video; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void omap4iss_video_cleanup(struct iss_video *video)
{
	media_entity_cleanup(&video->video.entity);
	mutex_destroy(&video->stream_lock);
	mutex_destroy(&video->mutex);
}