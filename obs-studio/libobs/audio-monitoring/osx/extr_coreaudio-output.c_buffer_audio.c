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
struct TYPE_2__ {int size; } ;
struct audio_monitor {int paused; int wait_size; int buffer_size; int /*<<< orphan*/  mutex; int /*<<< orphan*/  queue; TYPE_1__ empty_buffers; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  AudioQueueRef ;
typedef  int /*<<< orphan*/  AudioQueueBufferRef ;

/* Variables and functions */
 int /*<<< orphan*/  AudioQueuePause (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  circlebuf_push_back (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fill_buffer (struct audio_monitor*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void buffer_audio(void *data, AudioQueueRef aq, AudioQueueBufferRef buf)
{
	struct audio_monitor *monitor = data;

	pthread_mutex_lock(&monitor->mutex);
	circlebuf_push_back(&monitor->empty_buffers, &buf, sizeof(buf));
	while (monitor->empty_buffers.size > 0) {
		if (!fill_buffer(monitor)) {
			break;
		}
	}
	if (monitor->empty_buffers.size == sizeof(buf) * 3) {
		monitor->paused = true;
		monitor->wait_size = monitor->buffer_size * 3;
		AudioQueuePause(monitor->queue);
	}
	pthread_mutex_unlock(&monitor->mutex);

	UNUSED_PARAMETER(aq);
}