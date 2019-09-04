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
struct ffmpeg_output {int write_thread_active; int active; int /*<<< orphan*/  output; int /*<<< orphan*/  write_thread; int /*<<< orphan*/  stop_event; int /*<<< orphan*/  write_sem; } ;

/* Variables and functions */
 int ENOSPC ; 
 int OBS_OUTPUT_ERROR ; 
 int OBS_OUTPUT_NO_SPACE ; 
 int /*<<< orphan*/  ffmpeg_deactivate (struct ffmpeg_output*) ; 
 int /*<<< orphan*/  obs_output_signal_stop (int /*<<< orphan*/ ,int) ; 
 scalar_t__ os_event_try (int /*<<< orphan*/ ) ; 
 scalar_t__ os_sem_wait (int /*<<< orphan*/ ) ; 
 int process_packet (struct ffmpeg_output*) ; 
 int /*<<< orphan*/  pthread_detach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *write_thread(void *data)
{
	struct ffmpeg_output *output = data;

	while (os_sem_wait(output->write_sem) == 0) {
		/* check to see if shutting down */
		if (os_event_try(output->stop_event) == 0)
			break;

		int ret = process_packet(output);
		if (ret != 0) {
			int code = OBS_OUTPUT_ERROR;

			pthread_detach(output->write_thread);
			output->write_thread_active = false;

			if (ret == -ENOSPC)
				code = OBS_OUTPUT_NO_SPACE;

			obs_output_signal_stop(output->output, code);
			ffmpeg_deactivate(output);
			break;
		}
	}

	output->active = false;
	return NULL;
}