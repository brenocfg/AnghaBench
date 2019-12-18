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
struct hda_codec {struct conexant_spec* spec; } ;
struct conexant_spec {unsigned int gpio_led; scalar_t__ mute_led_polarity; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_GPIO_DATA ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*,unsigned int,int,unsigned int) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void cxt_update_gpio_led(struct hda_codec *codec, unsigned int mask,
				bool led_on)
{
	struct conexant_spec *spec = codec->spec;
	unsigned int oldval = spec->gpio_led;

	if (spec->mute_led_polarity)
		led_on = !led_on;

	if (led_on)
		spec->gpio_led |= mask;
	else
		spec->gpio_led &= ~mask;
	codec_dbg(codec, "mask:%d enabled:%d gpio_led:%d\n",
			mask, led_on, spec->gpio_led);
	if (spec->gpio_led != oldval)
		snd_hda_codec_write(codec, 0x01, 0, AC_VERB_SET_GPIO_DATA,
				    spec->gpio_led);
}