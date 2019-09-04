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
struct hda_gen_spec {int suppress_auto_mute; int suppress_auto_mic; int line_in_auto_switch; int auto_mute_via_amp; int need_dac_fix; int no_primary_hp; int no_multi_io; int multi_cap_vol; int inv_dmic_split; int indep_hp; int add_stereo_mix_input; int add_jack_modes; int power_down_unused; int hp_mic; int suppress_hp_mic_detect; int suppress_vmaster; int mixer_nid; } ;
struct hda_codec {int no_jack_detect; int inv_jack_detect; int no_trigger_sense; int inv_eapd; int pcm_format_first; int no_sticky_stream; int spdif_status_reset; int pin_amp_workaround; int single_adc_amp; int power_save_node; struct hda_gen_spec* spec; } ;

/* Variables and functions */
 int snd_hda_get_bool_hint (struct hda_codec*,char*) ; 
 int /*<<< orphan*/  snd_hda_get_int_hint (struct hda_codec*,char*,int*) ; 

__attribute__((used)) static void parse_user_hints(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;
	int val;

	val = snd_hda_get_bool_hint(codec, "jack_detect");
	if (val >= 0)
		codec->no_jack_detect = !val;
	val = snd_hda_get_bool_hint(codec, "inv_jack_detect");
	if (val >= 0)
		codec->inv_jack_detect = !!val;
	val = snd_hda_get_bool_hint(codec, "trigger_sense");
	if (val >= 0)
		codec->no_trigger_sense = !val;
	val = snd_hda_get_bool_hint(codec, "inv_eapd");
	if (val >= 0)
		codec->inv_eapd = !!val;
	val = snd_hda_get_bool_hint(codec, "pcm_format_first");
	if (val >= 0)
		codec->pcm_format_first = !!val;
	val = snd_hda_get_bool_hint(codec, "sticky_stream");
	if (val >= 0)
		codec->no_sticky_stream = !val;
	val = snd_hda_get_bool_hint(codec, "spdif_status_reset");
	if (val >= 0)
		codec->spdif_status_reset = !!val;
	val = snd_hda_get_bool_hint(codec, "pin_amp_workaround");
	if (val >= 0)
		codec->pin_amp_workaround = !!val;
	val = snd_hda_get_bool_hint(codec, "single_adc_amp");
	if (val >= 0)
		codec->single_adc_amp = !!val;
	val = snd_hda_get_bool_hint(codec, "power_save_node");
	if (val >= 0)
		codec->power_save_node = !!val;

	val = snd_hda_get_bool_hint(codec, "auto_mute");
	if (val >= 0)
		spec->suppress_auto_mute = !val;
	val = snd_hda_get_bool_hint(codec, "auto_mic");
	if (val >= 0)
		spec->suppress_auto_mic = !val;
	val = snd_hda_get_bool_hint(codec, "line_in_auto_switch");
	if (val >= 0)
		spec->line_in_auto_switch = !!val;
	val = snd_hda_get_bool_hint(codec, "auto_mute_via_amp");
	if (val >= 0)
		spec->auto_mute_via_amp = !!val;
	val = snd_hda_get_bool_hint(codec, "need_dac_fix");
	if (val >= 0)
		spec->need_dac_fix = !!val;
	val = snd_hda_get_bool_hint(codec, "primary_hp");
	if (val >= 0)
		spec->no_primary_hp = !val;
	val = snd_hda_get_bool_hint(codec, "multi_io");
	if (val >= 0)
		spec->no_multi_io = !val;
	val = snd_hda_get_bool_hint(codec, "multi_cap_vol");
	if (val >= 0)
		spec->multi_cap_vol = !!val;
	val = snd_hda_get_bool_hint(codec, "inv_dmic_split");
	if (val >= 0)
		spec->inv_dmic_split = !!val;
	val = snd_hda_get_bool_hint(codec, "indep_hp");
	if (val >= 0)
		spec->indep_hp = !!val;
	val = snd_hda_get_bool_hint(codec, "add_stereo_mix_input");
	if (val >= 0)
		spec->add_stereo_mix_input = !!val;
	/* the following two are just for compatibility */
	val = snd_hda_get_bool_hint(codec, "add_out_jack_modes");
	if (val >= 0)
		spec->add_jack_modes = !!val;
	val = snd_hda_get_bool_hint(codec, "add_in_jack_modes");
	if (val >= 0)
		spec->add_jack_modes = !!val;
	val = snd_hda_get_bool_hint(codec, "add_jack_modes");
	if (val >= 0)
		spec->add_jack_modes = !!val;
	val = snd_hda_get_bool_hint(codec, "power_down_unused");
	if (val >= 0)
		spec->power_down_unused = !!val;
	val = snd_hda_get_bool_hint(codec, "add_hp_mic");
	if (val >= 0)
		spec->hp_mic = !!val;
	val = snd_hda_get_bool_hint(codec, "hp_mic_detect");
	if (val >= 0)
		spec->suppress_hp_mic_detect = !val;
	val = snd_hda_get_bool_hint(codec, "vmaster");
	if (val >= 0)
		spec->suppress_vmaster = !val;

	if (!snd_hda_get_int_hint(codec, "mixer_nid", &val))
		spec->mixer_nid = val;
}