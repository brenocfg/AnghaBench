#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ array; } ;
struct audio_mix {TYPE_2__ inputs; } ;
struct TYPE_5__ {int /*<<< orphan*/  input_mutex; struct audio_mix* mixes; } ;
typedef  TYPE_1__ audio_t ;
typedef  int /*<<< orphan*/  audio_output_callback_t ;

/* Variables and functions */
 size_t DARRAY_INVALID ; 
 size_t MAX_AUDIO_MIXES ; 
 size_t audio_get_input_idx (TYPE_1__*,size_t,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  audio_input_free (scalar_t__) ; 
 int /*<<< orphan*/  da_erase (TYPE_2__,size_t) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void audio_output_disconnect(audio_t *audio, size_t mix_idx,
			     audio_output_callback_t callback, void *param)
{
	if (!audio || mix_idx >= MAX_AUDIO_MIXES)
		return;

	pthread_mutex_lock(&audio->input_mutex);

	size_t idx = audio_get_input_idx(audio, mix_idx, callback, param);
	if (idx != DARRAY_INVALID) {
		struct audio_mix *mix = &audio->mixes[mix_idx];
		audio_input_free(mix->inputs.array + idx);
		da_erase(mix->inputs, idx);
	}

	pthread_mutex_unlock(&audio->input_mutex);
}