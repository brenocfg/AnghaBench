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
struct hda_codec {struct cs_spec* spec; } ;
struct cs_spec {scalar_t__ sense_b; scalar_t__ gpio_mask; } ;

/* Variables and functions */
 unsigned int AC_DEFCFG_PORT_CONN ; 
 unsigned int AC_DEFCFG_PORT_CONN_SHIFT ; 
 unsigned int AC_JACK_PORT_NONE ; 
 int /*<<< orphan*/  CS421X_DMIC_PIN_NID ; 
 int /*<<< orphan*/  CS421X_IDX_DEV_CFG ; 
 unsigned int cs_vendor_coef_get (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs_vendor_coef_set (struct hda_codec*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ is_active_pin (struct hda_codec*,int /*<<< orphan*/ ) ; 
 unsigned int snd_hda_codec_get_pincfg (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_set_pincfg (struct hda_codec*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void cs4210_pinmux_init(struct hda_codec *codec)
{
	struct cs_spec *spec = codec->spec;
	unsigned int def_conf, coef;

	/* GPIO, DMIC_SCL, DMIC_SDA and SENSE_B are multiplexed */
	coef = cs_vendor_coef_get(codec, CS421X_IDX_DEV_CFG);

	if (spec->gpio_mask)
		coef |= 0x0008; /* B1,B2 are GPIOs */
	else
		coef &= ~0x0008;

	if (spec->sense_b)
		coef |= 0x0010; /* B2 is SENSE_B, not inverted  */
	else
		coef &= ~0x0010;

	cs_vendor_coef_set(codec, CS421X_IDX_DEV_CFG, coef);

	if ((spec->gpio_mask || spec->sense_b) &&
	    is_active_pin(codec, CS421X_DMIC_PIN_NID)) {

		/*
		    GPIO or SENSE_B forced - disconnect the DMIC pin.
		*/
		def_conf = snd_hda_codec_get_pincfg(codec, CS421X_DMIC_PIN_NID);
		def_conf &= ~AC_DEFCFG_PORT_CONN;
		def_conf |= (AC_JACK_PORT_NONE << AC_DEFCFG_PORT_CONN_SHIFT);
		snd_hda_codec_set_pincfg(codec, CS421X_DMIC_PIN_NID, def_conf);
	}
}