#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
struct obs_source_audio {int frames; int speakers; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  format; scalar_t__ samples_per_sec; int /*<<< orphan*/  const** data; int /*<<< orphan*/  member_0; } ;
struct audio_output_data {scalar_t__* data; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int (* audio_mix ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct audio_output_data*,size_t,size_t) ;} ;
struct TYPE_8__ {TYPE_2__ context; TYPE_1__ info; scalar_t__* audio_mix_buf; } ;
typedef  TYPE_3__ obs_source_t ;
typedef  enum speaker_layout { ____Placeholder_speaker_layout } speaker_layout ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_FORMAT_FLOAT_PLANAR ; 
 int AUDIO_OUTPUT_FRAMES ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  obs_source_output_audio (TYPE_3__*,struct obs_source_audio*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct audio_output_data*,size_t,size_t) ; 

__attribute__((used)) static void audio_submix(obs_source_t *source, size_t channels,
			 size_t sample_rate)
{
	struct audio_output_data audio_data;
	struct obs_source_audio audio = {0};
	bool success;
	uint64_t ts;

	for (size_t ch = 0; ch < channels; ch++) {
		audio_data.data[ch] = source->audio_mix_buf[ch];
	}

	memset(source->audio_mix_buf[0], 0,
	       sizeof(float) * AUDIO_OUTPUT_FRAMES * channels);

	success = source->info.audio_mix(source->context.data, &ts, &audio_data,
					 channels, sample_rate);

	if (!success)
		return;

	for (size_t i = 0; i < channels; i++)
		audio.data[i] = (const uint8_t *)audio_data.data[i];

	audio.samples_per_sec = (uint32_t)sample_rate;
	audio.frames = AUDIO_OUTPUT_FRAMES;
	audio.format = AUDIO_FORMAT_FLOAT_PLANAR;
	audio.speakers = (enum speaker_layout)channels;
	audio.timestamp = ts;

	obs_source_output_audio(source, &audio);
}