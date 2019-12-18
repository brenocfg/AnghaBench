#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct TYPE_6__ {scalar_t__ size; } ;
struct TYPE_8__ {scalar_t__ size; } ;
struct audio_monitor {int channels; scalar_t__ wait_size; int paused; int /*<<< orphan*/  mutex; int /*<<< orphan*/  queue; TYPE_1__ empty_buffers; TYPE_4__ new_data; int /*<<< orphan*/  resampler; int /*<<< orphan*/  active; } ;
struct audio_data {scalar_t__ frames; scalar_t__ data; } ;
struct TYPE_7__ {float user_volume; } ;
typedef  TYPE_2__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  AudioQueueStart (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EPSILON ; 
 int MAX_AV_PLANES ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (TYPE_2__*) ; 
 int audio_resampler_resample (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ *,int /*<<< orphan*/  const* const*,int) ; 
 int /*<<< orphan*/  circlebuf_push_back (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  close_float (float,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_buffer (struct audio_monitor*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_atomic_load_bool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void on_audio_playback(void *param, obs_source_t *source,
			      const struct audio_data *audio_data, bool muted)
{
	struct audio_monitor *monitor = param;
	float vol = source->user_volume;
	uint32_t bytes;

	UNUSED_PARAMETER(source);

	if (!os_atomic_load_bool(&monitor->active)) {
		return;
	}

	uint8_t *resample_data[MAX_AV_PLANES];
	uint32_t resample_frames;
	uint64_t ts_offset;
	bool success;

	success = audio_resampler_resample(
		monitor->resampler, resample_data, &resample_frames, &ts_offset,
		(const uint8_t *const *)audio_data->data,
		(uint32_t)audio_data->frames);
	if (!success) {
		return;
	}

	bytes = sizeof(float) * monitor->channels * resample_frames;

	if (muted) {
		memset(resample_data[0], 0, bytes);
	} else {
		/* apply volume */
		if (!close_float(vol, 1.0f, EPSILON)) {
			register float *cur = (float *)resample_data[0];
			register float *end =
				cur + resample_frames * monitor->channels;

			while (cur < end)
				*(cur++) *= vol;
		}
	}

	pthread_mutex_lock(&monitor->mutex);
	circlebuf_push_back(&monitor->new_data, resample_data[0], bytes);

	if (monitor->new_data.size >= monitor->wait_size) {
		monitor->wait_size = 0;

		while (monitor->empty_buffers.size > 0) {
			if (!fill_buffer(monitor)) {
				break;
			}
		}

		if (monitor->paused) {
			AudioQueueStart(monitor->queue, NULL);
			monitor->paused = false;
		}
	}

	pthread_mutex_unlock(&monitor->mutex);
}