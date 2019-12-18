#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct audio_data {int frames; int /*<<< orphan*/ * data; } ;
struct TYPE_7__ {scalar_t__ last_audio_input_buf_size; TYPE_5__* audio_input_buf; } ;
typedef  TYPE_2__ obs_source_t ;
typedef  int /*<<< orphan*/  audio_t ;
struct TYPE_9__ {scalar_t__ size; } ;
struct TYPE_6__ {int /*<<< orphan*/ * audio; } ;
struct TYPE_8__ {TYPE_1__ audio; } ;

/* Variables and functions */
 scalar_t__ MAX_BUF_SIZE ; 
 size_t audio_output_get_channels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  circlebuf_push_back (TYPE_5__*,int /*<<< orphan*/ ,size_t) ; 
 TYPE_4__* obs ; 

__attribute__((used)) static inline void source_output_audio_push_back(obs_source_t *source,
						 const struct audio_data *in)
{
	audio_t *audio = obs->audio.audio;
	size_t channels = audio_output_get_channels(audio);
	size_t size = in->frames * sizeof(float);

	/* do not allow the circular buffers to become too big */
	if ((source->audio_input_buf[0].size + size) > MAX_BUF_SIZE)
		return;

	for (size_t i = 0; i < channels; i++)
		circlebuf_push_back(&source->audio_input_buf[i], in->data[i],
				    size);

	/* reset audio input buffer size to ensure that audio doesn't get
	 * perpetually cut */
	source->last_audio_input_buf_size = 0;
}