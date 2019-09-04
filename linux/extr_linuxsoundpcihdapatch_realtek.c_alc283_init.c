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
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_AMP_GAIN_MUTE ; 
 int /*<<< orphan*/  AC_VERB_SET_PIN_WIDGET_CONTROL ; 
 int /*<<< orphan*/  AMP_OUT_MUTE ; 
 int /*<<< orphan*/  PIN_OUT ; 
 int /*<<< orphan*/  alc283_restore_default_value (struct hda_codec*) ; 
 int /*<<< orphan*/  alc_get_hp_pin (struct alc_spec*) ; 
 int /*<<< orphan*/  alc_update_coef_idx (struct hda_codec*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alc_write_coef_idx (struct hda_codec*,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_hda_jack_detect (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alc283_init(struct hda_codec *codec)
{
	struct alc_spec *spec = codec->spec;
	hda_nid_t hp_pin = alc_get_hp_pin(spec);
	bool hp_pin_sense;

	alc283_restore_default_value(codec);

	if (!hp_pin)
		return;

	msleep(30);
	hp_pin_sense = snd_hda_jack_detect(codec, hp_pin);

	/* Index 0x43 Direct Drive HP AMP LPM Control 1 */
	/* Headphone capless set to high power mode */
	alc_write_coef_idx(codec, 0x43, 0x9004);

	snd_hda_codec_write(codec, hp_pin, 0,
			    AC_VERB_SET_AMP_GAIN_MUTE, AMP_OUT_MUTE);

	if (hp_pin_sense)
		msleep(85);

	snd_hda_codec_write(codec, hp_pin, 0,
			    AC_VERB_SET_PIN_WIDGET_CONTROL, PIN_OUT);

	if (hp_pin_sense)
		msleep(85);
	/* Index 0x46 Combo jack auto switch control 2 */
	/* 3k pull low control for Headset jack. */
	alc_update_coef_idx(codec, 0x46, 3 << 12, 0);
	/* Headphone capless set to normal mode */
	alc_write_coef_idx(codec, 0x43, 0x9614);
}