#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hda_codec {struct alc_spec* spec; } ;
struct TYPE_3__ {int /*<<< orphan*/  hook; } ;
struct TYPE_4__ {TYPE_1__ vmaster_mute; } ;
struct alc_spec {unsigned int gpio_mute_led_mask; unsigned int gpio_mic_led_mask; TYPE_2__ gen; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  alc_fixup_gpio (struct hda_codec*,int,unsigned int) ; 
 int /*<<< orphan*/  alc_fixup_gpio_mute_hook ; 
 int /*<<< orphan*/  alc_gpio_micmute_update ; 
 int /*<<< orphan*/  snd_hda_gen_add_micmute_led (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alc_fixup_hp_gpio_led(struct hda_codec *codec,
				  int action,
				  unsigned int mute_mask,
				  unsigned int micmute_mask)
{
	struct alc_spec *spec = codec->spec;

	alc_fixup_gpio(codec, action, mute_mask | micmute_mask);

	if (action != HDA_FIXUP_ACT_PRE_PROBE)
		return;
	if (mute_mask) {
		spec->gpio_mute_led_mask = mute_mask;
		spec->gen.vmaster_mute.hook = alc_fixup_gpio_mute_hook;
	}
	if (micmute_mask) {
		spec->gpio_mic_led_mask = micmute_mask;
		snd_hda_gen_add_micmute_led(codec, alc_gpio_micmute_update);
	}
}