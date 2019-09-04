#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hda_fixup {int dummy; } ;
struct hda_codec {struct ad198x_spec* spec; } ;
struct TYPE_5__ {int /*<<< orphan*/ * speaker_pins; int /*<<< orphan*/ * line_out_pins; int /*<<< orphan*/  line_out_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  hook; } ;
struct TYPE_6__ {int own_eapd_ctl; TYPE_2__ autocfg; TYPE_1__ vmaster_mute; } ;
struct ad198x_spec {TYPE_3__ gen; int /*<<< orphan*/  eapd_nid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_GPIO_DATA ; 
 int /*<<< orphan*/  AC_VERB_SET_GPIO_DIRECTION ; 
 int /*<<< orphan*/  AC_VERB_SET_GPIO_MASK ; 
 int /*<<< orphan*/  AUTO_PIN_SPEAKER_OUT ; 
#define  HDA_FIXUP_ACT_PRE_PROBE 129 
#define  HDA_FIXUP_ACT_PROBE 128 
 int /*<<< orphan*/  ad1884_vmaster_hp_gpio_hook ; 
 int /*<<< orphan*/  snd_hda_codec_write_cache (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ad1884_fixup_hp_eapd(struct hda_codec *codec,
				 const struct hda_fixup *fix, int action)
{
	struct ad198x_spec *spec = codec->spec;

	switch (action) {
	case HDA_FIXUP_ACT_PRE_PROBE:
		spec->gen.vmaster_mute.hook = ad1884_vmaster_hp_gpio_hook;
		spec->gen.own_eapd_ctl = 1;
		snd_hda_codec_write_cache(codec, 0x01, 0,
					  AC_VERB_SET_GPIO_MASK, 0x02);
		snd_hda_codec_write_cache(codec, 0x01, 0,
					  AC_VERB_SET_GPIO_DIRECTION, 0x02);
		snd_hda_codec_write_cache(codec, 0x01, 0,
					  AC_VERB_SET_GPIO_DATA, 0x02);
		break;
	case HDA_FIXUP_ACT_PROBE:
		if (spec->gen.autocfg.line_out_type == AUTO_PIN_SPEAKER_OUT)
			spec->eapd_nid = spec->gen.autocfg.line_out_pins[0];
		else
			spec->eapd_nid = spec->gen.autocfg.speaker_pins[0];
		break;
	}
}