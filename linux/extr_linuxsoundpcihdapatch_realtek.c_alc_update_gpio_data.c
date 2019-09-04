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
struct alc_spec {unsigned int gpio_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  alc_write_gpio_data (struct hda_codec*) ; 

__attribute__((used)) static void alc_update_gpio_data(struct hda_codec *codec, unsigned int mask,
				 bool on)
{
	struct alc_spec *spec = codec->spec;
	unsigned int oldval = spec->gpio_data;

	if (on)
		spec->gpio_data |= mask;
	else
		spec->gpio_data &= ~mask;
	if (oldval != spec->gpio_data)
		alc_write_gpio_data(codec);
}