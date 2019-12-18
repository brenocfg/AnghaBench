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
struct obs_core_video {int thread_initialized; int /*<<< orphan*/  video_thread; scalar_t__ video; } ;
struct TYPE_2__ {struct obs_core_video video; } ;

/* Variables and functions */
 TYPE_1__* obs ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  video_output_stop (scalar_t__) ; 

__attribute__((used)) static void stop_video(void)
{
	struct obs_core_video *video = &obs->video;
	void *thread_retval;

	if (video->video) {
		video_output_stop(video->video);
		if (video->thread_initialized) {
			pthread_join(video->video_thread, &thread_retval);
			video->thread_initialized = false;
		}
	}
}