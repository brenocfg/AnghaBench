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
struct hda_codec {struct alc_spec* spec; } ;
struct alc_spec {scalar_t__ mute_led_polarity; } ;

/* Variables and functions */
 int /*<<< orphan*/  alc_update_gpio_data (struct hda_codec*,unsigned int,int) ; 

__attribute__((used)) static void alc_update_gpio_led(struct hda_codec *codec, unsigned int mask,
				bool enabled)
{
	struct alc_spec *spec = codec->spec;

	if (spec->mute_led_polarity)
		enabled = !enabled;
	alc_update_gpio_data(codec, mask, !enabled); /* muted -> LED on */
}