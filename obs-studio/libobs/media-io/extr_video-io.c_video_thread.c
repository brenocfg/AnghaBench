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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct video_output {int /*<<< orphan*/  total_frames; scalar_t__ stop; int /*<<< orphan*/  update_semaphore; TYPE_1__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  obs_get_profiler_name_store () ; 
 int /*<<< orphan*/  os_atomic_inc_long (int /*<<< orphan*/ *) ; 
 scalar_t__ os_sem_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_set_thread_name (char*) ; 
 int /*<<< orphan*/  profile_end (char const*) ; 
 int /*<<< orphan*/  profile_reenable_thread () ; 
 int /*<<< orphan*/  profile_start (char const*) ; 
 char* profile_store_name (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_output_cur_frame (struct video_output*) ; 

__attribute__((used)) static void *video_thread(void *param)
{
	struct video_output *video = param;

	os_set_thread_name("video-io: video thread");

	const char *video_thread_name =
		profile_store_name(obs_get_profiler_name_store(),
				   "video_thread(%s)", video->info.name);

	while (os_sem_wait(video->update_semaphore) == 0) {
		if (video->stop)
			break;

		profile_start(video_thread_name);
		while (!video->stop && !video_output_cur_frame(video)) {
			os_atomic_inc_long(&video->total_frames);
		}

		os_atomic_inc_long(&video->total_frames);
		profile_end(video_thread_name);

		profile_reenable_thread();
	}

	return NULL;
}