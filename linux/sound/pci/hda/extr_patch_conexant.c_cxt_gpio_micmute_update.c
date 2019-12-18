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
struct hda_codec {struct conexant_spec* spec; } ;
struct TYPE_3__ {int /*<<< orphan*/  led_value; } ;
struct TYPE_4__ {TYPE_1__ micmute_led; } ;
struct conexant_spec {TYPE_2__ gen; int /*<<< orphan*/  gpio_mic_led_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxt_update_gpio_led (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cxt_gpio_micmute_update(struct hda_codec *codec)
{
	struct conexant_spec *spec = codec->spec;

	cxt_update_gpio_led(codec, spec->gpio_mic_led_mask,
			    spec->gen.micmute_led.led_value);
}