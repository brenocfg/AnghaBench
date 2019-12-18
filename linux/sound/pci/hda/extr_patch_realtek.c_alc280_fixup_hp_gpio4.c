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
struct hda_fixup {int dummy; } ;
struct hda_codec {int /*<<< orphan*/  power_filter; struct alc_spec* spec; } ;
struct alc_spec {int cap_mute_led_nid; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  alc_cap_micmute_update ; 
 int /*<<< orphan*/  alc_fixup_hp_gpio_led (struct hda_codec*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_power_filter ; 
 int /*<<< orphan*/  snd_hda_gen_add_micmute_led (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alc280_fixup_hp_gpio4(struct hda_codec *codec,
				   const struct hda_fixup *fix, int action)
{
	struct alc_spec *spec = codec->spec;

	alc_fixup_hp_gpio_led(codec, action, 0x08, 0);
	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		spec->cap_mute_led_nid = 0x18;
		snd_hda_gen_add_micmute_led(codec, alc_cap_micmute_update);
		codec->power_filter = led_power_filter;
	}
}