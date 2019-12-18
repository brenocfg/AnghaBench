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
struct TYPE_3__ {scalar_t__ led_value; } ;
struct TYPE_4__ {TYPE_1__ micmute_led; } ;
struct sigmatel_spec {int /*<<< orphan*/  gpio_data; int /*<<< orphan*/  gpio_dir; int /*<<< orphan*/  gpio_mask; int /*<<< orphan*/  mic_mute_led_gpio; TYPE_2__ gen; } ;
struct hda_codec {struct sigmatel_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  stac_gpio_set (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stac_capture_led_update(struct hda_codec *codec)
{
	struct sigmatel_spec *spec = codec->spec;

	if (spec->gen.micmute_led.led_value)
		spec->gpio_data |= spec->mic_mute_led_gpio;
	else
		spec->gpio_data &= ~spec->mic_mute_led_gpio;
	stac_gpio_set(codec, spec->gpio_mask, spec->gpio_dir, spec->gpio_data);
}