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
struct alc_spec {int /*<<< orphan*/  no_shutup_pins; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_AMP_GAIN_MUTE ; 
 int /*<<< orphan*/  AC_VERB_SET_PIN_WIDGET_CONTROL ; 
 int AMP_OUT_MUTE ; 
 int /*<<< orphan*/  alc_get_hp_pin (struct alc_spec*) ; 
 int alc_read_coefex_idx (struct hda_codec*,int,int) ; 
 int /*<<< orphan*/  alc_update_coef_idx (struct hda_codec*,int,int,int) ; 
 int /*<<< orphan*/  alc_update_coefex_idx (struct hda_codec*,int,int,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void alc294_hp_init(struct hda_codec *codec)
{
	struct alc_spec *spec = codec->spec;
	hda_nid_t hp_pin = alc_get_hp_pin(spec);
	int i, val;

	if (!hp_pin)
		return;

	snd_hda_codec_write(codec, hp_pin, 0,
			    AC_VERB_SET_AMP_GAIN_MUTE, AMP_OUT_MUTE);

	msleep(100);

	if (!spec->no_shutup_pins)
		snd_hda_codec_write(codec, hp_pin, 0,
				    AC_VERB_SET_PIN_WIDGET_CONTROL, 0x0);

	alc_update_coef_idx(codec, 0x6f, 0x000f, 0);/* Set HP depop to manual mode */
	alc_update_coefex_idx(codec, 0x58, 0x00, 0x8000, 0x8000); /* HP depop procedure start */

	/* Wait for depop procedure finish  */
	val = alc_read_coefex_idx(codec, 0x58, 0x01);
	for (i = 0; i < 20 && val & 0x0080; i++) {
		msleep(50);
		val = alc_read_coefex_idx(codec, 0x58, 0x01);
	}
	/* Set HP depop to auto mode */
	alc_update_coef_idx(codec, 0x6f, 0x000f, 0x000b);
	msleep(50);
}