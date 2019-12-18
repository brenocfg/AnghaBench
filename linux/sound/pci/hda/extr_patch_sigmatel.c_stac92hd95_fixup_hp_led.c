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
struct sigmatel_spec {int /*<<< orphan*/  gpio_led_polarity; int /*<<< orphan*/  gpio_led; int /*<<< orphan*/  default_polarity; } ;
struct hda_fixup {int dummy; } ;
struct hda_codec {struct sigmatel_spec* spec; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ find_mute_led_cfg (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stac92hd95_fixup_hp_led(struct hda_codec *codec,
				    const struct hda_fixup *fix, int action)
{
	struct sigmatel_spec *spec = codec->spec;

	if (action != HDA_FIXUP_ACT_PRE_PROBE)
		return;

	if (find_mute_led_cfg(codec, spec->default_polarity))
		codec_dbg(codec, "mute LED gpio %d polarity %d\n",
				spec->gpio_led,
				spec->gpio_led_polarity);
}