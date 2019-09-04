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
struct alc_spec {int /*<<< orphan*/  gpio_mute_led_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  alc_update_gpio_led (struct hda_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void alc_fixup_gpio_mute_hook(void *private_data, int enabled)
{
	struct hda_codec *codec = private_data;
	struct alc_spec *spec = codec->spec;

	alc_update_gpio_led(codec, spec->gpio_mute_led_mask, enabled);
}