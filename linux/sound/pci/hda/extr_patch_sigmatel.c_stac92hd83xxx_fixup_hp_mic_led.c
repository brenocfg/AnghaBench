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
struct sigmatel_spec {int mic_mute_led_gpio; } ;
struct hda_fixup {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  power_caps; } ;
struct hda_codec {TYPE_1__ core; struct sigmatel_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_PWRST_CLKSTOP ; 
 int HDA_FIXUP_ACT_PRE_PROBE ; 

__attribute__((used)) static void stac92hd83xxx_fixup_hp_mic_led(struct hda_codec *codec,
				   const struct hda_fixup *fix, int action)
{
	struct sigmatel_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		spec->mic_mute_led_gpio = 0x08; /* GPIO3 */
#ifdef CONFIG_PM
		/* resetting controller clears GPIO, so we need to keep on */
		codec->core.power_caps &= ~AC_PWRST_CLKSTOP;
#endif
	}
}