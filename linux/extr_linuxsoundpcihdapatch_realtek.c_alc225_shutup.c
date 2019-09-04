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
struct hda_codec {struct alc_spec* spec; } ;
struct alc_spec {int dummy; } ;
typedef  int hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_AMP_GAIN_MUTE ; 
 int /*<<< orphan*/  AC_VERB_SET_PIN_WIDGET_CONTROL ; 
 int AMP_OUT_MUTE ; 
 int /*<<< orphan*/  alc269_shutup (struct hda_codec*) ; 
 int /*<<< orphan*/  alc_auto_setup_eapd (struct hda_codec*,int) ; 
 int alc_get_hp_pin (struct alc_spec*) ; 
 int /*<<< orphan*/  alc_shutup_pins (struct hda_codec*) ; 
 int /*<<< orphan*/  alc_update_coef_idx (struct hda_codec*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int snd_hda_jack_detect (struct hda_codec*,int) ; 

__attribute__((used)) static void alc225_shutup(struct hda_codec *codec)
{
	struct alc_spec *spec = codec->spec;
	hda_nid_t hp_pin = alc_get_hp_pin(spec);
	bool hp1_pin_sense, hp2_pin_sense;

	if (!hp_pin) {
		alc269_shutup(codec);
		return;
	}

	/* 3k pull low control for Headset jack. */
	alc_update_coef_idx(codec, 0x4a, 0, 3 << 10);

	hp1_pin_sense = snd_hda_jack_detect(codec, hp_pin);
	hp2_pin_sense = snd_hda_jack_detect(codec, 0x16);

	if (hp1_pin_sense || hp2_pin_sense)
		msleep(2);

	if (hp1_pin_sense)
		snd_hda_codec_write(codec, hp_pin, 0,
			    AC_VERB_SET_AMP_GAIN_MUTE, AMP_OUT_MUTE);
	if (hp2_pin_sense)
		snd_hda_codec_write(codec, 0x16, 0,
			    AC_VERB_SET_AMP_GAIN_MUTE, AMP_OUT_MUTE);

	if (hp1_pin_sense || hp2_pin_sense)
		msleep(85);

	if (hp1_pin_sense)
		snd_hda_codec_write(codec, hp_pin, 0,
			    AC_VERB_SET_PIN_WIDGET_CONTROL, 0x0);
	if (hp2_pin_sense)
		snd_hda_codec_write(codec, 0x16, 0,
			    AC_VERB_SET_PIN_WIDGET_CONTROL, 0x0);

	if (hp1_pin_sense || hp2_pin_sense)
		msleep(100);

	alc_auto_setup_eapd(codec, false);
	alc_shutup_pins(codec);
}