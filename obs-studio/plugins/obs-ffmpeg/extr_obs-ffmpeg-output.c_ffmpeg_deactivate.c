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
struct TYPE_2__ {size_t num; scalar_t__ array; } ;
struct ffmpeg_output {int write_thread_active; int /*<<< orphan*/  ff_data; int /*<<< orphan*/  write_mutex; TYPE_1__ packets; int /*<<< orphan*/  write_thread; int /*<<< orphan*/  write_sem; int /*<<< orphan*/  stop_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_free_packet (scalar_t__) ; 
 int /*<<< orphan*/  da_free (TYPE_1__) ; 
 int /*<<< orphan*/  ffmpeg_data_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_event_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_sem_post (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ffmpeg_deactivate(struct ffmpeg_output *output)
{
	if (output->write_thread_active) {
		os_event_signal(output->stop_event);
		os_sem_post(output->write_sem);
		pthread_join(output->write_thread, NULL);
		output->write_thread_active = false;
	}

	pthread_mutex_lock(&output->write_mutex);

	for (size_t i = 0; i < output->packets.num; i++)
		av_free_packet(output->packets.array + i);
	da_free(output->packets);

	pthread_mutex_unlock(&output->write_mutex);

	ffmpeg_data_free(&output->ff_data);
}