#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct compressor_data {int max_sidechain_frames; size_t num_channels; int /*<<< orphan*/  sidechain_mutex; TYPE_1__* sidechain_data; } ;
struct audio_data {int frames; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  obs_source_t ;
struct TYPE_4__ {size_t size; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  circlebuf_pop_front (TYPE_1__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  circlebuf_push_back (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  circlebuf_push_back_zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sidechain_capture(void *param, obs_source_t *source,
			      const struct audio_data *audio_data, bool muted)
{
	struct compressor_data *cd = param;

	UNUSED_PARAMETER(source);

	pthread_mutex_lock(&cd->sidechain_mutex);

	if (cd->max_sidechain_frames < audio_data->frames)
		cd->max_sidechain_frames = audio_data->frames;

	size_t expected_size = cd->max_sidechain_frames * sizeof(float);

	if (!expected_size)
		goto unlock;

	if (cd->sidechain_data[0].size > expected_size * 2) {
		for (size_t i = 0; i < cd->num_channels; i++) {
			circlebuf_pop_front(&cd->sidechain_data[i], NULL,
					    expected_size);
		}
	}

	if (muted) {
		for (size_t i = 0; i < cd->num_channels; i++) {
			circlebuf_push_back_zero(&cd->sidechain_data[i],
						 audio_data->frames *
							 sizeof(float));
		}
	} else {
		for (size_t i = 0; i < cd->num_channels; i++) {
			circlebuf_push_back(&cd->sidechain_data[i],
					    audio_data->data[i],
					    audio_data->frames * sizeof(float));
		}
	}

unlock:
	pthread_mutex_unlock(&cd->sidechain_mutex);
}