#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hda_pcm {TYPE_4__* stream; scalar_t__ pcm_type; } ;
struct TYPE_6__ {scalar_t__ num_dacs; scalar_t__ dig_out_nid; int /*<<< orphan*/  slave_dig_outs; int /*<<< orphan*/  max_channels; scalar_t__* dac_nids; } ;
struct TYPE_5__ {scalar_t__ line_out_type; int line_outs; } ;
struct hda_gen_spec {int num_adc_nids; scalar_t__* adc_nids; int /*<<< orphan*/ * stream_analog_alt_capture; scalar_t__ alt_dac_nid; int /*<<< orphan*/ * stream_analog_alt_playback; struct hda_pcm** pcm_rec; int /*<<< orphan*/  stream_name_alt_analog; int /*<<< orphan*/  auto_mic; scalar_t__ dyn_adc_switch; scalar_t__ no_analog; scalar_t__ dig_in_nid; int /*<<< orphan*/ * stream_digital_capture; TYPE_2__ multiout; int /*<<< orphan*/ * stream_digital_playback; scalar_t__ dig_out_type; int /*<<< orphan*/  stream_name_digital; int /*<<< orphan*/ * stream_analog_capture; TYPE_1__ autocfg; int /*<<< orphan*/ * stream_analog_playback; int /*<<< orphan*/  stream_name_analog; } ;
struct TYPE_7__ {int /*<<< orphan*/  chip_name; } ;
struct hda_codec {TYPE_3__ core; int /*<<< orphan*/  slave_dig_outs; struct hda_gen_spec* spec; } ;
struct TYPE_8__ {int substreams; int /*<<< orphan*/  chmap; int /*<<< orphan*/  channels_max; } ;

/* Variables and functions */
 scalar_t__ AUTO_PIN_SPEAKER_OUT ; 
 int ENOMEM ; 
 scalar_t__ HDA_PCM_TYPE_SPDIF ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  dyn_adc_pcm_analog_capture ; 
 int /*<<< orphan*/  fill_pcm_stream_name (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_analog_alt_capture ; 
 int /*<<< orphan*/  pcm_analog_alt_playback ; 
 int /*<<< orphan*/  pcm_analog_capture ; 
 int /*<<< orphan*/  pcm_analog_playback ; 
 int /*<<< orphan*/  pcm_digital_capture ; 
 int /*<<< orphan*/  pcm_digital_playback ; 
 int /*<<< orphan*/  pcm_null_stream ; 
 int /*<<< orphan*/  setup_pcm_stream (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 struct hda_pcm* snd_hda_codec_pcm_new (struct hda_codec*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_2_1_chmaps ; 

int snd_hda_gen_build_pcms(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;
	struct hda_pcm *info;
	bool have_multi_adcs;

	if (spec->no_analog)
		goto skip_analog;

	fill_pcm_stream_name(spec->stream_name_analog,
			     sizeof(spec->stream_name_analog),
			     " Analog", codec->core.chip_name);
	info = snd_hda_codec_pcm_new(codec, "%s", spec->stream_name_analog);
	if (!info)
		return -ENOMEM;
	spec->pcm_rec[0] = info;

	if (spec->multiout.num_dacs > 0) {
		setup_pcm_stream(&info->stream[SNDRV_PCM_STREAM_PLAYBACK],
				 &pcm_analog_playback,
				 spec->stream_analog_playback,
				 spec->multiout.dac_nids[0]);
		info->stream[SNDRV_PCM_STREAM_PLAYBACK].channels_max =
			spec->multiout.max_channels;
		if (spec->autocfg.line_out_type == AUTO_PIN_SPEAKER_OUT &&
		    spec->autocfg.line_outs == 2)
			info->stream[SNDRV_PCM_STREAM_PLAYBACK].chmap =
				snd_pcm_2_1_chmaps;
	}
	if (spec->num_adc_nids) {
		setup_pcm_stream(&info->stream[SNDRV_PCM_STREAM_CAPTURE],
				 (spec->dyn_adc_switch ?
				  &dyn_adc_pcm_analog_capture : &pcm_analog_capture),
				 spec->stream_analog_capture,
				 spec->adc_nids[0]);
	}

 skip_analog:
	/* SPDIF for stream index #1 */
	if (spec->multiout.dig_out_nid || spec->dig_in_nid) {
		fill_pcm_stream_name(spec->stream_name_digital,
				     sizeof(spec->stream_name_digital),
				     " Digital", codec->core.chip_name);
		info = snd_hda_codec_pcm_new(codec, "%s",
					     spec->stream_name_digital);
		if (!info)
			return -ENOMEM;
		codec->slave_dig_outs = spec->multiout.slave_dig_outs;
		spec->pcm_rec[1] = info;
		if (spec->dig_out_type)
			info->pcm_type = spec->dig_out_type;
		else
			info->pcm_type = HDA_PCM_TYPE_SPDIF;
		if (spec->multiout.dig_out_nid)
			setup_pcm_stream(&info->stream[SNDRV_PCM_STREAM_PLAYBACK],
					 &pcm_digital_playback,
					 spec->stream_digital_playback,
					 spec->multiout.dig_out_nid);
		if (spec->dig_in_nid)
			setup_pcm_stream(&info->stream[SNDRV_PCM_STREAM_CAPTURE],
					 &pcm_digital_capture,
					 spec->stream_digital_capture,
					 spec->dig_in_nid);
	}

	if (spec->no_analog)
		return 0;

	/* If the use of more than one ADC is requested for the current
	 * model, configure a second analog capture-only PCM.
	 */
	have_multi_adcs = (spec->num_adc_nids > 1) &&
		!spec->dyn_adc_switch && !spec->auto_mic;
	/* Additional Analaog capture for index #2 */
	if (spec->alt_dac_nid || have_multi_adcs) {
		fill_pcm_stream_name(spec->stream_name_alt_analog,
				     sizeof(spec->stream_name_alt_analog),
			     " Alt Analog", codec->core.chip_name);
		info = snd_hda_codec_pcm_new(codec, "%s",
					     spec->stream_name_alt_analog);
		if (!info)
			return -ENOMEM;
		spec->pcm_rec[2] = info;
		if (spec->alt_dac_nid)
			setup_pcm_stream(&info->stream[SNDRV_PCM_STREAM_PLAYBACK],
					 &pcm_analog_alt_playback,
					 spec->stream_analog_alt_playback,
					 spec->alt_dac_nid);
		else
			setup_pcm_stream(&info->stream[SNDRV_PCM_STREAM_PLAYBACK],
					 &pcm_null_stream, NULL, 0);
		if (have_multi_adcs) {
			setup_pcm_stream(&info->stream[SNDRV_PCM_STREAM_CAPTURE],
					 &pcm_analog_alt_capture,
					 spec->stream_analog_alt_capture,
					 spec->adc_nids[1]);
			info->stream[SNDRV_PCM_STREAM_CAPTURE].substreams =
				spec->num_adc_nids - 1;
		} else {
			setup_pcm_stream(&info->stream[SNDRV_PCM_STREAM_CAPTURE],
					 &pcm_null_stream, NULL, 0);
		}
	}

	return 0;
}