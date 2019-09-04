#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
struct snd_pcm_hw_constraint_list {int dummy; } ;
struct hdmi_spec {int /*<<< orphan*/  multiout; } ;
struct hda_pcm_stream {int dummy; } ;
struct hda_codec {TYPE_1__* preset; struct hdmi_spec* spec; } ;
struct TYPE_2__ {int vendor_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 struct snd_pcm_hw_constraint_list hw_constraints_2_6_8_channels ; 
 struct snd_pcm_hw_constraint_list hw_constraints_2_8_channels ; 
 int snd_hda_multi_out_dig_open (struct hda_codec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_pcm_hw_constraint_list const*) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_step (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int simple_playback_pcm_open(struct hda_pcm_stream *hinfo,
				    struct hda_codec *codec,
				    struct snd_pcm_substream *substream)
{
	struct hdmi_spec *spec = codec->spec;
	const struct snd_pcm_hw_constraint_list *hw_constraints_channels = NULL;

	switch (codec->preset->vendor_id) {
	case 0x10de0002:
	case 0x10de0003:
	case 0x10de0005:
	case 0x10de0006:
		hw_constraints_channels = &hw_constraints_2_8_channels;
		break;
	case 0x10de0007:
		hw_constraints_channels = &hw_constraints_2_6_8_channels;
		break;
	default:
		break;
	}

	if (hw_constraints_channels != NULL) {
		snd_pcm_hw_constraint_list(substream->runtime, 0,
				SNDRV_PCM_HW_PARAM_CHANNELS,
				hw_constraints_channels);
	} else {
		snd_pcm_hw_constraint_step(substream->runtime, 0,
					   SNDRV_PCM_HW_PARAM_CHANNELS, 2);
	}

	return snd_hda_multi_out_dig_open(codec, &spec->multiout);
}