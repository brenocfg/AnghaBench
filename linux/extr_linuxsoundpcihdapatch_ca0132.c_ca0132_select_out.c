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
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {int* vnode_lswitch; scalar_t__ cur_out_type; int /*<<< orphan*/ * out_pins; int /*<<< orphan*/  unsol_tag_hp; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_GET_PIN_WIDGET_CONTROL ; 
 int /*<<< orphan*/  AC_VERB_SET_EAPD_BTLENABLE ; 
 unsigned int FLOAT_ONE ; 
 unsigned int FLOAT_ZERO ; 
 scalar_t__ HEADPHONE_OUT ; 
 unsigned int PIN_HP ; 
 unsigned int PIN_OUT ; 
 scalar_t__ SPEAKER_OUT ; 
 int /*<<< orphan*/  VENDOR_CHIPIO_EAPD_SEL_SET ; 
 size_t VNID_HP_ASEL ; 
 size_t VNID_HP_SEL ; 
 size_t VNODE_START_NID ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*) ; 
 int dspio_set_uint_param (struct hda_codec*,int,int,unsigned int) ; 
 unsigned int snd_hda_codec_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int snd_hda_jack_detect (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_power_down_pm (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_power_up_pm (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_set_pin_ctl (struct hda_codec*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ca0132_select_out(struct hda_codec *codec)
{
	struct ca0132_spec *spec = codec->spec;
	unsigned int pin_ctl;
	int jack_present;
	int auto_jack;
	unsigned int tmp;
	int err;

	codec_dbg(codec, "ca0132_select_out\n");

	snd_hda_power_up_pm(codec);

	auto_jack = spec->vnode_lswitch[VNID_HP_ASEL - VNODE_START_NID];

	if (auto_jack)
		jack_present = snd_hda_jack_detect(codec, spec->unsol_tag_hp);
	else
		jack_present =
			spec->vnode_lswitch[VNID_HP_SEL - VNODE_START_NID];

	if (jack_present)
		spec->cur_out_type = HEADPHONE_OUT;
	else
		spec->cur_out_type = SPEAKER_OUT;

	if (spec->cur_out_type == SPEAKER_OUT) {
		codec_dbg(codec, "ca0132_select_out speaker\n");
		/*speaker out config*/
		tmp = FLOAT_ONE;
		err = dspio_set_uint_param(codec, 0x80, 0x04, tmp);
		if (err < 0)
			goto exit;
		/*enable speaker EQ*/
		tmp = FLOAT_ONE;
		err = dspio_set_uint_param(codec, 0x8f, 0x00, tmp);
		if (err < 0)
			goto exit;

		/* Setup EAPD */
		snd_hda_codec_write(codec, spec->out_pins[1], 0,
				    VENDOR_CHIPIO_EAPD_SEL_SET, 0x02);
		snd_hda_codec_write(codec, spec->out_pins[0], 0,
				    AC_VERB_SET_EAPD_BTLENABLE, 0x00);
		snd_hda_codec_write(codec, spec->out_pins[0], 0,
				    VENDOR_CHIPIO_EAPD_SEL_SET, 0x00);
		snd_hda_codec_write(codec, spec->out_pins[0], 0,
				    AC_VERB_SET_EAPD_BTLENABLE, 0x02);

		/* disable headphone node */
		pin_ctl = snd_hda_codec_read(codec, spec->out_pins[1], 0,
					AC_VERB_GET_PIN_WIDGET_CONTROL, 0);
		snd_hda_set_pin_ctl(codec, spec->out_pins[1],
				    pin_ctl & ~PIN_HP);
		/* enable speaker node */
		pin_ctl = snd_hda_codec_read(codec, spec->out_pins[0], 0,
				AC_VERB_GET_PIN_WIDGET_CONTROL, 0);
		snd_hda_set_pin_ctl(codec, spec->out_pins[0],
				    pin_ctl | PIN_OUT);
	} else {
		codec_dbg(codec, "ca0132_select_out hp\n");
		/*headphone out config*/
		tmp = FLOAT_ZERO;
		err = dspio_set_uint_param(codec, 0x80, 0x04, tmp);
		if (err < 0)
			goto exit;
		/*disable speaker EQ*/
		tmp = FLOAT_ZERO;
		err = dspio_set_uint_param(codec, 0x8f, 0x00, tmp);
		if (err < 0)
			goto exit;

		/* Setup EAPD */
		snd_hda_codec_write(codec, spec->out_pins[0], 0,
				    VENDOR_CHIPIO_EAPD_SEL_SET, 0x00);
		snd_hda_codec_write(codec, spec->out_pins[0], 0,
				    AC_VERB_SET_EAPD_BTLENABLE, 0x00);
		snd_hda_codec_write(codec, spec->out_pins[1], 0,
				    VENDOR_CHIPIO_EAPD_SEL_SET, 0x02);
		snd_hda_codec_write(codec, spec->out_pins[0], 0,
				    AC_VERB_SET_EAPD_BTLENABLE, 0x02);

		/* disable speaker*/
		pin_ctl = snd_hda_codec_read(codec, spec->out_pins[0], 0,
					AC_VERB_GET_PIN_WIDGET_CONTROL, 0);
		snd_hda_set_pin_ctl(codec, spec->out_pins[0],
				    pin_ctl & ~PIN_HP);
		/* enable headphone*/
		pin_ctl = snd_hda_codec_read(codec, spec->out_pins[1], 0,
					AC_VERB_GET_PIN_WIDGET_CONTROL, 0);
		snd_hda_set_pin_ctl(codec, spec->out_pins[1],
				    pin_ctl | PIN_HP);
	}

exit:
	snd_hda_power_down_pm(codec);

	return err < 0 ? err : 0;
}