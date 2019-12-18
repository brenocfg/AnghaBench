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
struct sigmatel_spec {int /*<<< orphan*/  gpio_led_polarity; int /*<<< orphan*/  gpio_led; } ;
struct hda_fixup {int dummy; } ;
struct hda_codec {struct sigmatel_spec* spec; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ find_mute_led_cfg (struct hda_codec*,int) ; 
 int /*<<< orphan*/  fixup_hp_headphone (struct hda_codec*,int) ; 
 scalar_t__ is_hp_output (struct hda_codec*,int) ; 

__attribute__((used)) static void stac92hd71bxx_fixup_hp(struct hda_codec *codec,
				   const struct hda_fixup *fix, int action)
{
	struct sigmatel_spec *spec = codec->spec;

	if (action != HDA_FIXUP_ACT_PRE_PROBE)
		return;

	/* when both output A and F are assigned, these are supposedly
	 * dock and built-in headphones; fix both pin configs
	 */
	if (is_hp_output(codec, 0x0a) && is_hp_output(codec, 0x0f)) {
		fixup_hp_headphone(codec, 0x0a);
		fixup_hp_headphone(codec, 0x0f);
	}

	if (find_mute_led_cfg(codec, 1))
		codec_dbg(codec, "mute LED gpio %d polarity %d\n",
				spec->gpio_led,
				spec->gpio_led_polarity);

}