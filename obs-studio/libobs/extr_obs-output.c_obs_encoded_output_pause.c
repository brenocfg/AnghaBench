#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
struct TYPE_8__ {TYPE_2__** audio_encoders; TYPE_2__* video_encoder; } ;
typedef  TYPE_1__ obs_output_t ;
struct TYPE_10__ {int /*<<< orphan*/  mutex; void* ts_start; } ;
struct TYPE_9__ {TYPE_3__ pause; int /*<<< orphan*/  paused; } ;
typedef  TYPE_2__ obs_encoder_t ;

/* Variables and functions */
 int MAX_AUDIO_MIXES ; 
 int /*<<< orphan*/  end_pause (TYPE_3__*,void*) ; 
 void* get_closest_v_ts (TYPE_3__*) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pause_can_start (TYPE_3__*) ; 
 int /*<<< orphan*/  pause_can_stop (TYPE_3__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool obs_encoded_output_pause(obs_output_t *output, bool pause)
{
	obs_encoder_t *venc;
	obs_encoder_t *aenc[MAX_AUDIO_MIXES];
	uint64_t closest_v_ts;
	bool success = false;

	venc = output->video_encoder;
	for (size_t i = 0; i < MAX_AUDIO_MIXES; i++)
		aenc[i] = output->audio_encoders[i];

	pthread_mutex_lock(&venc->pause.mutex);
	for (size_t i = 0; i < MAX_AUDIO_MIXES; i++) {
		if (aenc[i]) {
			pthread_mutex_lock(&aenc[i]->pause.mutex);
		}
	}

	/* ---------------------------- */

	closest_v_ts = get_closest_v_ts(&venc->pause);

	if (pause) {
		if (!pause_can_start(&venc->pause)) {
			goto fail;
		}
		for (size_t i = 0; i < MAX_AUDIO_MIXES; i++) {
			if (aenc[i] && !pause_can_start(&aenc[i]->pause)) {
				goto fail;
			}
		}

		os_atomic_set_bool(&venc->paused, true);
		venc->pause.ts_start = closest_v_ts;

		for (size_t i = 0; i < MAX_AUDIO_MIXES; i++) {
			if (aenc[i]) {
				os_atomic_set_bool(&aenc[i]->paused, true);
				aenc[i]->pause.ts_start = closest_v_ts;
			}
		}
	} else {
		if (!pause_can_stop(&venc->pause)) {
			goto fail;
		}
		for (size_t i = 0; i < MAX_AUDIO_MIXES; i++) {
			if (aenc[i] && !pause_can_stop(&aenc[i]->pause)) {
				goto fail;
			}
		}

		os_atomic_set_bool(&venc->paused, false);
		end_pause(&venc->pause, closest_v_ts);

		for (size_t i = 0; i < MAX_AUDIO_MIXES; i++) {
			if (aenc[i]) {
				os_atomic_set_bool(&aenc[i]->paused, false);
				end_pause(&aenc[i]->pause, closest_v_ts);
			}
		}
	}

	/* ---------------------------- */

	success = true;

fail:
	for (size_t i = MAX_AUDIO_MIXES; i > 0; i--) {
		if (aenc[i - 1]) {
			pthread_mutex_unlock(&aenc[i - 1]->pause.mutex);
		}
	}
	pthread_mutex_unlock(&venc->pause.mutex);

	return success;
}