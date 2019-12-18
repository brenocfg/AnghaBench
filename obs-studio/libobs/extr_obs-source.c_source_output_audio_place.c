#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct audio_data {int frames; scalar_t__ timestamp; int /*<<< orphan*/ * data; } ;
struct TYPE_9__ {scalar_t__ audio_ts; scalar_t__ last_audio_input_buf_size; TYPE_6__* audio_input_buf; } ;
typedef  TYPE_2__ obs_source_t ;
typedef  int /*<<< orphan*/  audio_t ;
struct TYPE_11__ {scalar_t__ size; } ;
struct TYPE_8__ {int /*<<< orphan*/ * audio; } ;
struct TYPE_10__ {TYPE_1__ audio; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 size_t MAX_BUF_SIZE ; 
 size_t audio_output_get_channels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,unsigned long,unsigned long,unsigned long,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  circlebuf_place (TYPE_6__*,size_t,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  circlebuf_pop_back (TYPE_6__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int get_buf_placement (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_5__* obs ; 
 int /*<<< orphan*/  reset_audio_data (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static void source_output_audio_place(obs_source_t *source,
				      const struct audio_data *in)
{
	audio_t *audio = obs->audio.audio;
	size_t buf_placement;
	size_t channels = audio_output_get_channels(audio);
	size_t size = in->frames * sizeof(float);

	if (!source->audio_ts || in->timestamp < source->audio_ts)
		reset_audio_data(source, in->timestamp);

	buf_placement =
		get_buf_placement(audio, in->timestamp - source->audio_ts) *
		sizeof(float);

#if DEBUG_AUDIO == 1
	blog(LOG_DEBUG,
	     "frames: %lu, size: %lu, placement: %lu, base_ts: %llu, ts: %llu",
	     (unsigned long)in->frames,
	     (unsigned long)source->audio_input_buf[0].size,
	     (unsigned long)buf_placement, source->audio_ts, in->timestamp);
#endif

	/* do not allow the circular buffers to become too big */
	if ((buf_placement + size) > MAX_BUF_SIZE)
		return;

	for (size_t i = 0; i < channels; i++) {
		circlebuf_place(&source->audio_input_buf[i], buf_placement,
				in->data[i], size);
		circlebuf_pop_back(&source->audio_input_buf[i], NULL,
				   source->audio_input_buf[i].size -
					   (buf_placement + size));
	}

	source->last_audio_input_buf_size = 0;
}