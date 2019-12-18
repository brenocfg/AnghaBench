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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  size_t uint32_t ;
struct audio_monitor {size_t bytes_per_frame; size_t frames; int /*<<< orphan*/  playback_mutex; int /*<<< orphan*/  packets; int /*<<< orphan*/  new_data; int /*<<< orphan*/  resampler; } ;
struct audio_data {scalar_t__ frames; scalar_t__ data; } ;
struct TYPE_3__ {float user_volume; int /*<<< orphan*/  activate_refs; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPSILON ; 
 int MAX_AV_PLANES ; 
 int audio_resampler_resample (int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/  const* const*,size_t) ; 
 int /*<<< orphan*/  circlebuf_push_back (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  close_float (float,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_stream_write (void*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ os_atomic_load_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_volume (struct audio_monitor*,float,int /*<<< orphan*/ **,size_t) ; 
 scalar_t__ pthread_mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void on_audio_playback(void *param, obs_source_t *source,
			      const struct audio_data *audio_data, bool muted)
{
	struct audio_monitor *monitor = param;
	float vol = source->user_volume;
	size_t bytes;

	uint8_t *resample_data[MAX_AV_PLANES];
	uint32_t resample_frames;
	uint64_t ts_offset;
	bool success;

	if (pthread_mutex_trylock(&monitor->playback_mutex) != 0)
		return;

	if (os_atomic_load_long(&source->activate_refs) == 0)
		goto unlock;

	success = audio_resampler_resample(
		monitor->resampler, resample_data, &resample_frames, &ts_offset,
		(const uint8_t *const *)audio_data->data,
		(uint32_t)audio_data->frames);

	if (!success)
		goto unlock;

	bytes = monitor->bytes_per_frame * resample_frames;

	if (muted) {
		memset(resample_data[0], 0, bytes);
	} else {
		if (!close_float(vol, 1.0f, EPSILON)) {
			process_volume(monitor, vol, resample_data,
				       resample_frames);
		}
	}

	circlebuf_push_back(&monitor->new_data, resample_data[0], bytes);
	monitor->packets++;
	monitor->frames += resample_frames;

unlock:
	pthread_mutex_unlock(&monitor->playback_mutex);
	do_stream_write(param);
}