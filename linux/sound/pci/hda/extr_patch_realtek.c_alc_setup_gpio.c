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
struct alc_spec {unsigned int gpio_mask; unsigned int gpio_dir; unsigned int gpio_data; } ;

/* Variables and functions */

__attribute__((used)) static void alc_setup_gpio(struct hda_codec *codec, unsigned int mask)
{
	struct alc_spec *spec = codec->spec;

	spec->gpio_mask |= mask;
	spec->gpio_dir |= mask;
	spec->gpio_data |= mask;
}