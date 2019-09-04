#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int audio_pending; int audio_mixers; int /*<<< orphan*/ ** audio_output_buf; int /*<<< orphan*/  audio_buf_mutex; TYPE_3__* audio_input_buf; } ;
typedef  TYPE_1__ obs_source_t ;
struct TYPE_6__ {size_t size; } ;

/* Variables and functions */
 size_t MAX_AUDIO_MIXES ; 
 int /*<<< orphan*/  apply_audio_volume (TYPE_1__*,int,size_t,size_t) ; 
 int /*<<< orphan*/  circlebuf_peek_front (TYPE_3__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void process_audio_source_tick(obs_source_t *source,
		uint32_t mixers, size_t channels, size_t sample_rate,
		size_t size)
{
	pthread_mutex_lock(&source->audio_buf_mutex);

	if (source->audio_input_buf[0].size < size) {
		source->audio_pending = true;
		pthread_mutex_unlock(&source->audio_buf_mutex);
		return;
	}

	for (size_t ch = 0; ch < channels; ch++)
		circlebuf_peek_front(&source->audio_input_buf[ch],
				source->audio_output_buf[0][ch],
				size);

	pthread_mutex_unlock(&source->audio_buf_mutex);

	for (size_t mix = 1; mix < MAX_AUDIO_MIXES; mix++) {
		uint32_t mix_and_val = (1 << mix);

		if ((source->audio_mixers & mix_and_val) == 0 ||
		    (mixers & mix_and_val) == 0) {
			memset(source->audio_output_buf[mix][0],
					0, size * channels);
			continue;
		}

		for (size_t ch = 0; ch < channels; ch++)
			memcpy(source->audio_output_buf[mix][ch],
					source->audio_output_buf[0][ch], size);
	}

	if ((source->audio_mixers & 1) == 0 || (mixers & 1) == 0)
		memset(source->audio_output_buf[0][0], 0,
				size * channels);

	apply_audio_volume(source, mixers, channels, sample_rate);
	source->audio_pending = false;
}