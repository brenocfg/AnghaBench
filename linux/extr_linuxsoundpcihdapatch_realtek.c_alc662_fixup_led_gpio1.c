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
struct alc_spec {int mute_led_polarity; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  alc_fixup_hp_gpio_led (struct hda_codec*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_led_power_filter ; 

__attribute__((used)) static void alc662_fixup_led_gpio1(struct hda_codec *codec,
				   const struct hda_fixup *fix, int action)
{
	struct alc_spec *spec = codec->spec;

	alc_fixup_hp_gpio_led(codec, action, 0x01, 0);
	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		spec->mute_led_polarity = 1;
		codec->power_filter = gpio_led_power_filter;
	}
}