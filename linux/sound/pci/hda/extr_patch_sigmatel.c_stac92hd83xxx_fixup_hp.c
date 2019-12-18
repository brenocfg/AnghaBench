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
struct TYPE_2__ {int line_in_auto_switch; } ;
struct sigmatel_spec {TYPE_1__ gen; int /*<<< orphan*/  gpio_led_polarity; int /*<<< orphan*/  gpio_led; int /*<<< orphan*/  default_polarity; } ;
struct hda_fixup {int dummy; } ;
struct hda_codec {struct sigmatel_spec* spec; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ find_mute_led_cfg (struct hda_codec*,int /*<<< orphan*/ ) ; 
 scalar_t__ hp_bnb2011_with_dock (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_codec_set_pincfg (struct hda_codec*,int,int) ; 

__attribute__((used)) static void stac92hd83xxx_fixup_hp(struct hda_codec *codec,
				   const struct hda_fixup *fix, int action)
{
	struct sigmatel_spec *spec = codec->spec;

	if (action != HDA_FIXUP_ACT_PRE_PROBE)
		return;

	if (hp_bnb2011_with_dock(codec)) {
		snd_hda_codec_set_pincfg(codec, 0xa, 0x2101201f);
		snd_hda_codec_set_pincfg(codec, 0xf, 0x2181205e);
	}

	if (find_mute_led_cfg(codec, spec->default_polarity))
		codec_dbg(codec, "mute LED gpio %d polarity %d\n",
				spec->gpio_led,
				spec->gpio_led_polarity);

	/* allow auto-switching of dock line-in */
	spec->gen.line_in_auto_switch = true;
}