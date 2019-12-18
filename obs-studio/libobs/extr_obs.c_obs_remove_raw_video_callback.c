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
struct obs_core_video {int /*<<< orphan*/  video; } ;
struct TYPE_2__ {struct obs_core_video video; } ;

/* Variables and functions */
 TYPE_1__* obs ; 
 int /*<<< orphan*/  stop_raw_video (int /*<<< orphan*/ ,void (*) (void*,struct video_data*),void*) ; 

void obs_remove_raw_video_callback(void (*callback)(void *param,
						    struct video_data *frame),
				   void *param)
{
	struct obs_core_video *video = &obs->video;
	if (!obs)
		return;
	stop_raw_video(video->video, callback, param);
}