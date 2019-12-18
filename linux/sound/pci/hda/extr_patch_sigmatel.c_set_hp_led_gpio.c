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
struct sigmatel_spec {int gpio_led; } ;
struct TYPE_2__ {int /*<<< orphan*/  afg; } ;
struct hda_codec {TYPE_1__ core; struct sigmatel_spec* spec; } ;

/* Variables and functions */
 unsigned int AC_GPIO_IO_COUNT ; 
 int /*<<< orphan*/  AC_PAR_GPIO_CAP ; 
 unsigned int snd_hda_param_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_hp_led_gpio(struct hda_codec *codec)
{
	struct sigmatel_spec *spec = codec->spec;
	unsigned int gpio;

	if (spec->gpio_led)
		return;

	gpio = snd_hda_param_read(codec, codec->core.afg, AC_PAR_GPIO_CAP);
	gpio &= AC_GPIO_IO_COUNT;
	if (gpio > 3)
		spec->gpio_led = 0x08; /* GPIO 3 */
	else
		spec->gpio_led = 0x01; /* GPIO 0 */
}