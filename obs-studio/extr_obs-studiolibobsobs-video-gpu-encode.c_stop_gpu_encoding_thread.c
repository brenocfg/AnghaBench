#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct obs_core_video {int gpu_encode_thread_initialized; int /*<<< orphan*/  gpu_encode_thread; int /*<<< orphan*/  gpu_encode_semaphore; int /*<<< orphan*/  gpu_encode_stop; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_sem_post (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void stop_gpu_encoding_thread(struct obs_core_video *video)
{
	if (video->gpu_encode_thread_initialized) {
		os_atomic_set_bool(&video->gpu_encode_stop, true);
		os_sem_post(video->gpu_encode_semaphore);
		pthread_join(video->gpu_encode_thread, NULL);
		video->gpu_encode_thread_initialized = false;
	}
}