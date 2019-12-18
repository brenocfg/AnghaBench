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
struct TYPE_3__ {int initialized; int stop; int /*<<< orphan*/  thread; int /*<<< orphan*/  update_semaphore; } ;
typedef  TYPE_1__ video_t ;

/* Variables and functions */
 int /*<<< orphan*/  os_sem_post (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,void**) ; 

void video_output_stop(video_t *video)
{
	void *thread_ret;

	if (!video)
		return;

	if (video->initialized) {
		video->initialized = false;
		video->stop = true;
		os_sem_post(video->update_semaphore);
		pthread_join(video->thread, &thread_ret);
	}
}