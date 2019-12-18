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
struct alc_spec {scalar_t__ ultra_low_power; } ;
typedef  int hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_AMP_GAIN_MUTE ; 
 int /*<<< orphan*/  AC_VERB_SET_PIN_WIDGET_CONTROL ; 
 int AMP_OUT_MUTE ; 
 int /*<<< orphan*/  alc_auto_setup_eapd (struct hda_codec*,int) ; 
 int alc_get_hp_pin (struct alc_spec*) ; 
 int /*<<< orphan*/  alc_shutup_pins (struct hda_codec*) ; 
 int /*<<< orphan*/  alc_update_coef_idx (struct hda_codec*,int,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int snd_hda_jack_detect (struct hda_codec*,int) ; 

__attribute__((used)) static void alc225_shutup(struct hda_codec *codec)
{
	struct alc_spec *spec = codec->spec;
	hda_nid_t hp_pin = alc_get_hp_pin(spec);
	bool hp1_pin_sense, hp2_pin_sense;

	if (!hp_pin)
		hp_pin = 0x21;
	/* 3k pull low control for Headset jack. */
	alc_update_coef_idx(codec, 0x4a, 0, 3 << 10);

	hp1_pin_sense = snd_hda_jack_detect(codec, hp_pin);
	hp2_pin_sense = snd_hda_jack_detect(codec, 0x16);

	if (hp1_pin_sense || hp2_pin_sense)
		msleep(2);

	if (hp1_pin_sense || spec->ultra_low_power)
		snd_hda_codec_write(codec, hp_pin, 0,
			    AC_VERB_SET_AMP_GAIN_MUTE, AMP_OUT_MUTE);
	if (hp2_pin_sense)
		snd_hda_codec_write(codec, 0x16, 0,
			    AC_VERB_SET_AMP_GAIN_MUTE, AMP_OUT_MUTE);

	if (hp1_pin_sense || hp2_pin_sense || spec->ultra_low_power)
		msleep(85);

	if (hp1_pin_sense || spec->ultra_low_power)
		snd_hda_codec_write(codec, hp_pin, 0,
			    AC_VERB_SET_PIN_WIDGET_CONTROL, 0x0);
	if (hp2_pin_sense)
		snd_hda_codec_write(codec, 0x16, 0,
			    AC_VERB_SET_PIN_WIDGET_CONTROL, 0x0);

	if (hp1_pin_sense || hp2_pin_sense || spec->ultra_low_power)
		msleep(100);

	alc_auto_setup_eapd(codec, false);
	alc_shutup_pins(codec);
	if (spec->ultra_low_power) {
		msleep(50);
		alc_update_coef_idx(codec, 0x08, 0x0f << 2, 0x0c << 2);
		alc_update_coef_idx(codec, 0x0e, 7<<6, 0);
		alc_update_coef_idx(codec, 0x33, 1<<11, 1<<11);
		alc_update_coef_idx(codec, 0x4a, 3<<4, 2<<4);
		msleep(30);
	}
}