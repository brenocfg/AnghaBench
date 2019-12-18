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
struct hda_verb {int member_0; int member_2; int /*<<< orphan*/  member_1; } ;
struct hda_fixup {int dummy; } ;
struct hda_codec {struct conexant_spec* spec; } ;
struct TYPE_3__ {int /*<<< orphan*/  hook; } ;
struct TYPE_4__ {TYPE_1__ vmaster_mute; } ;
struct conexant_spec {int gpio_mute_led_mask; int gpio_mic_led_mask; scalar_t__ gpio_led; scalar_t__ mute_led_polarity; TYPE_2__ gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_GPIO_DATA ; 
#define  AC_VERB_SET_GPIO_DIRECTION 129 
#define  AC_VERB_SET_GPIO_MASK 128 
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  cxt_fixup_gpio_mute_hook ; 
 int /*<<< orphan*/  cxt_gpio_micmute_update ; 
 int /*<<< orphan*/  snd_hda_add_verbs (struct hda_codec*,struct hda_verb const*) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  snd_hda_gen_add_micmute_led (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cxt_fixup_mute_led_gpio(struct hda_codec *codec,
				const struct hda_fixup *fix, int action)
{
	struct conexant_spec *spec = codec->spec;
	static const struct hda_verb gpio_init[] = {
		{ 0x01, AC_VERB_SET_GPIO_MASK, 0x03 },
		{ 0x01, AC_VERB_SET_GPIO_DIRECTION, 0x03 },
		{}
	};

	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		spec->gen.vmaster_mute.hook = cxt_fixup_gpio_mute_hook;
		spec->gpio_led = 0;
		spec->mute_led_polarity = 0;
		spec->gpio_mute_led_mask = 0x01;
		spec->gpio_mic_led_mask = 0x02;
		snd_hda_gen_add_micmute_led(codec, cxt_gpio_micmute_update);
	}
	snd_hda_add_verbs(codec, gpio_init);
	if (spec->gpio_led)
		snd_hda_codec_write(codec, 0x01, 0, AC_VERB_SET_GPIO_DATA,
				    spec->gpio_led);
}