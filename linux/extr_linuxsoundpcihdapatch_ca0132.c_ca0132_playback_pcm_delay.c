#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {unsigned int rate; } ;
struct hda_pcm_stream {int dummy; } ;
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {scalar_t__ dsp_state; scalar_t__ cur_out_type; scalar_t__* effects_switch; } ;

/* Variables and functions */
 size_t DIALOG_PLUS ; 
 scalar_t__ DSP_DOWNLOADED ; 
 unsigned int DSP_PLAYBACK_INIT_LATENCY ; 
 scalar_t__ DSP_PLAY_ENHANCEMENT_LATENCY ; 
 scalar_t__ DSP_SPEAKER_OUT_LATENCY ; 
 size_t EFFECT_START_NID ; 
 size_t PLAY_ENHANCEMENT ; 
 scalar_t__ SPEAKER_OUT ; 
 size_t SURROUND ; 

__attribute__((used)) static unsigned int ca0132_playback_pcm_delay(struct hda_pcm_stream *info,
			struct hda_codec *codec,
			struct snd_pcm_substream *substream)
{
	struct ca0132_spec *spec = codec->spec;
	unsigned int latency = DSP_PLAYBACK_INIT_LATENCY;
	struct snd_pcm_runtime *runtime = substream->runtime;

	if (spec->dsp_state != DSP_DOWNLOADED)
		return 0;

	/* Add latency if playback enhancement and either effect is enabled. */
	if (spec->effects_switch[PLAY_ENHANCEMENT - EFFECT_START_NID]) {
		if ((spec->effects_switch[SURROUND - EFFECT_START_NID]) ||
		    (spec->effects_switch[DIALOG_PLUS - EFFECT_START_NID]))
			latency += DSP_PLAY_ENHANCEMENT_LATENCY;
	}

	/* Applying Speaker EQ adds latency as well. */
	if (spec->cur_out_type == SPEAKER_OUT)
		latency += DSP_SPEAKER_OUT_LATENCY;

	return (latency * runtime->rate) / 1000;
}