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
struct ffmpeg_output {int /*<<< orphan*/  stop_event; int /*<<< orphan*/  write_sem; int /*<<< orphan*/  write_mutex; int /*<<< orphan*/  start_thread; scalar_t__ connecting; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (void*) ; 
 int /*<<< orphan*/  ffmpeg_output_full_stop (struct ffmpeg_output*) ; 
 int /*<<< orphan*/  os_event_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_sem_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ffmpeg_output_destroy(void *data)
{
	struct ffmpeg_output *output = data;

	if (output) {
		if (output->connecting)
			pthread_join(output->start_thread, NULL);

		ffmpeg_output_full_stop(output);

		pthread_mutex_destroy(&output->write_mutex);
		os_sem_destroy(output->write_sem);
		os_event_destroy(output->stop_event);
		bfree(data);
	}
}