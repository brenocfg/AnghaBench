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
struct audio_monitor {int /*<<< orphan*/  mutex; int /*<<< orphan*/  new_data; int /*<<< orphan*/  empty_buffers; int /*<<< orphan*/  resampler; scalar_t__ queue; scalar_t__* buffers; scalar_t__ active; scalar_t__ source; } ;

/* Variables and functions */
 int /*<<< orphan*/  AudioQueueDispose (scalar_t__,int) ; 
 int /*<<< orphan*/  AudioQueueFreeBuffer (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  AudioQueueStop (scalar_t__,int) ; 
 int /*<<< orphan*/  audio_resampler_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  circlebuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_source_remove_audio_capture_callback (scalar_t__,int /*<<< orphan*/ ,struct audio_monitor*) ; 
 int /*<<< orphan*/  on_audio_playback ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void audio_monitor_free(struct audio_monitor *monitor)
{
	if (monitor->source) {
		obs_source_remove_audio_capture_callback(
			monitor->source, on_audio_playback, monitor);
	}
	if (monitor->active) {
		AudioQueueStop(monitor->queue, true);
	}
	for (size_t i = 0; i < 3; i++) {
		if (monitor->buffers[i]) {
			AudioQueueFreeBuffer(monitor->queue,
					     monitor->buffers[i]);
		}
	}
	if (monitor->queue) {
		AudioQueueDispose(monitor->queue, true);
	}

	audio_resampler_destroy(monitor->resampler);
	circlebuf_free(&monitor->empty_buffers);
	circlebuf_free(&monitor->new_data);
	pthread_mutex_destroy(&monitor->mutex);
}