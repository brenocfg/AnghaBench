#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct obs_video_info {unsigned long long fps_den; unsigned long long fps_num; } ;
struct TYPE_3__ {int /*<<< orphan*/  limit_framerate; } ;
struct game_capture {TYPE_2__* global_hook_info; TYPE_1__ config; } ;
struct TYPE_4__ {int frame_interval; } ;

/* Variables and functions */
 scalar_t__ obs_get_video_info (struct obs_video_info*) ; 

__attribute__((used)) static inline void reset_frame_interval(struct game_capture *gc)
{
	struct obs_video_info ovi;
	uint64_t interval = 0;

	if (obs_get_video_info(&ovi)) {
		interval = ovi.fps_den * 1000000000ULL / ovi.fps_num;

		/* Always limit capture framerate to some extent.  If a game
		 * running at 900 FPS is being captured without some sort of
		 * limited capture interval, it will dramatically reduce
		 * performance. */
		if (!gc->config.limit_framerate)
			interval /= 2;
	}

	gc->global_hook_info->frame_interval = interval;
}