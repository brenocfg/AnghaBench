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
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {scalar_t__ mem_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  writew (unsigned short,scalar_t__) ; 

__attribute__((used)) static void ca0113_mmio_gpio_set(struct hda_codec *codec, unsigned int gpio_pin,
		bool enable)
{
	struct ca0132_spec *spec = codec->spec;
	unsigned short gpio_data;

	gpio_data = gpio_pin & 0xF;
	gpio_data |= ((enable << 8) & 0x100);

	writew(gpio_data, spec->mem_base + 0x320);
}