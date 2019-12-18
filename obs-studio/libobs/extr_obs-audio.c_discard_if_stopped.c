#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {size_t last_audio_input_buf_size; int pending_stop; scalar_t__ audio_ts; TYPE_4__* audio_input_buf; TYPE_1__ context; } ;
typedef  TYPE_2__ obs_source_t ;
struct TYPE_7__ {size_t size; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  circlebuf_pop_front (TYPE_4__*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static bool discard_if_stopped(obs_source_t *source, size_t channels)
{
	size_t last_size;
	size_t size;

	last_size = source->last_audio_input_buf_size;
	size = source->audio_input_buf[0].size;

	if (!size)
		return false;

	/* if perpetually pending data, it means the audio has stopped,
	 * so clear the audio data */
	if (last_size == size) {
		if (!source->pending_stop) {
			source->pending_stop = true;
#if DEBUG_AUDIO == 1
			blog(LOG_DEBUG, "doing pending stop trick: '%s'",
			     source->context.name);
#endif
			return true;
		}

		for (size_t ch = 0; ch < channels; ch++)
			circlebuf_pop_front(&source->audio_input_buf[ch], NULL,
					    source->audio_input_buf[ch].size);

		source->pending_stop = false;
		source->audio_ts = 0;
		source->last_audio_input_buf_size = 0;
#if DEBUG_AUDIO == 1
		blog(LOG_DEBUG, "source audio data appears to have "
				"stopped, clearing");
#endif
		return true;
	} else {
		source->last_audio_input_buf_size = size;
		return false;
	}
}