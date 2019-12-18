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
struct TYPE_6__ {size_t num; scalar_t__ array; } ;
struct audio_mix {TYPE_2__ inputs; } ;
struct TYPE_5__ {int /*<<< orphan*/  stop_event; struct audio_mix* mixes; int /*<<< orphan*/  thread; scalar_t__ initialized; } ;
typedef  TYPE_1__ audio_t ;

/* Variables and functions */
 size_t MAX_AUDIO_MIXES ; 
 int /*<<< orphan*/  audio_input_free (scalar_t__) ; 
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 int /*<<< orphan*/  da_free (TYPE_2__) ; 
 int /*<<< orphan*/  os_event_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_event_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,void**) ; 

void audio_output_close(audio_t *audio)
{
	void *thread_ret;

	if (!audio)
		return;

	if (audio->initialized) {
		os_event_signal(audio->stop_event);
		pthread_join(audio->thread, &thread_ret);
	}

	for (size_t mix_idx = 0; mix_idx < MAX_AUDIO_MIXES; mix_idx++) {
		struct audio_mix *mix = &audio->mixes[mix_idx];

		for (size_t i = 0; i < mix->inputs.num; i++)
			audio_input_free(mix->inputs.array + i);

		da_free(mix->inputs);
	}

	os_event_destroy(audio->stop_event);
	bfree(audio);
}