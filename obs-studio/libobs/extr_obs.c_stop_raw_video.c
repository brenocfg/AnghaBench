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
typedef  int /*<<< orphan*/  video_t ;
struct obs_core_video {int /*<<< orphan*/  raw_active; } ;
struct TYPE_2__ {struct obs_core_video video; } ;

/* Variables and functions */
 TYPE_1__* obs ; 
 int /*<<< orphan*/  os_atomic_dec_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_output_disconnect (int /*<<< orphan*/ *,void (*) (void*,struct video_data*),void*) ; 

void stop_raw_video(video_t *v,
		    void (*callback)(void *param, struct video_data *frame),
		    void *param)
{
	struct obs_core_video *video = &obs->video;
	os_atomic_dec_long(&video->raw_active);
	video_output_disconnect(v, callback, param);
}