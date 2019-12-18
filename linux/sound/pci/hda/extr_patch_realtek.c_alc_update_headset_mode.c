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
struct hda_codec {struct alc_spec* spec; } ;
struct TYPE_2__ {scalar_t__* imux_pins; size_t* cur_mux; int hp_jack_present; } ;
struct alc_spec {scalar_t__ headset_mic_pin; scalar_t__ headphone_mic_pin; int current_headset_mode; TYPE_1__ gen; int /*<<< orphan*/  current_headset_type; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 int AC_PINCTL_HP_EN ; 
 int AC_PINCTL_OUT_EN ; 
#define  ALC_HEADSET_MODE_HEADPHONE 131 
#define  ALC_HEADSET_MODE_HEADSET 130 
#define  ALC_HEADSET_MODE_MIC 129 
 int ALC_HEADSET_MODE_UNKNOWN ; 
#define  ALC_HEADSET_MODE_UNPLUGGED 128 
 int /*<<< orphan*/  ALC_HEADSET_TYPE_CTIA ; 
 int /*<<< orphan*/  ALC_HEADSET_TYPE_OMTP ; 
 int /*<<< orphan*/  ALC_HEADSET_TYPE_UNKNOWN ; 
 int PIN_VREFHIZ ; 
 int /*<<< orphan*/  alc_determine_headset_type (struct hda_codec*) ; 
 scalar_t__ alc_get_hp_pin (struct alc_spec*) ; 
 int /*<<< orphan*/  alc_headset_mode_ctia (struct hda_codec*) ; 
 int /*<<< orphan*/  alc_headset_mode_default (struct hda_codec*) ; 
 int /*<<< orphan*/  alc_headset_mode_mic_in (struct hda_codec*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  alc_headset_mode_omtp (struct hda_codec*) ; 
 int /*<<< orphan*/  alc_headset_mode_unplugged (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_gen_update_outputs (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_jack_detect (struct hda_codec*,scalar_t__) ; 
 int /*<<< orphan*/  snd_hda_set_pin_ctl_cache (struct hda_codec*,scalar_t__,int) ; 

__attribute__((used)) static void alc_update_headset_mode(struct hda_codec *codec)
{
	struct alc_spec *spec = codec->spec;

	hda_nid_t mux_pin = spec->gen.imux_pins[spec->gen.cur_mux[0]];
	hda_nid_t hp_pin = alc_get_hp_pin(spec);

	int new_headset_mode;

	if (!snd_hda_jack_detect(codec, hp_pin))
		new_headset_mode = ALC_HEADSET_MODE_UNPLUGGED;
	else if (mux_pin == spec->headset_mic_pin)
		new_headset_mode = ALC_HEADSET_MODE_HEADSET;
	else if (mux_pin == spec->headphone_mic_pin)
		new_headset_mode = ALC_HEADSET_MODE_MIC;
	else
		new_headset_mode = ALC_HEADSET_MODE_HEADPHONE;

	if (new_headset_mode == spec->current_headset_mode) {
		snd_hda_gen_update_outputs(codec);
		return;
	}

	switch (new_headset_mode) {
	case ALC_HEADSET_MODE_UNPLUGGED:
		alc_headset_mode_unplugged(codec);
		spec->current_headset_mode = ALC_HEADSET_MODE_UNKNOWN;
		spec->current_headset_type = ALC_HEADSET_TYPE_UNKNOWN;
		spec->gen.hp_jack_present = false;
		break;
	case ALC_HEADSET_MODE_HEADSET:
		if (spec->current_headset_type == ALC_HEADSET_TYPE_UNKNOWN)
			alc_determine_headset_type(codec);
		if (spec->current_headset_type == ALC_HEADSET_TYPE_CTIA)
			alc_headset_mode_ctia(codec);
		else if (spec->current_headset_type == ALC_HEADSET_TYPE_OMTP)
			alc_headset_mode_omtp(codec);
		spec->gen.hp_jack_present = true;
		break;
	case ALC_HEADSET_MODE_MIC:
		alc_headset_mode_mic_in(codec, hp_pin, spec->headphone_mic_pin);
		spec->gen.hp_jack_present = false;
		break;
	case ALC_HEADSET_MODE_HEADPHONE:
		alc_headset_mode_default(codec);
		spec->gen.hp_jack_present = true;
		break;
	}
	if (new_headset_mode != ALC_HEADSET_MODE_MIC) {
		snd_hda_set_pin_ctl_cache(codec, hp_pin,
					  AC_PINCTL_OUT_EN | AC_PINCTL_HP_EN);
		if (spec->headphone_mic_pin && spec->headphone_mic_pin != hp_pin)
			snd_hda_set_pin_ctl_cache(codec, spec->headphone_mic_pin,
						  PIN_VREFHIZ);
	}
	spec->current_headset_mode = new_headset_mode;

	snd_hda_gen_update_outputs(codec);
}