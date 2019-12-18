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
 int /*<<< orphan*/  ca0113_mmio_gpio_set (struct hda_codec*,int,int) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void sbz_region2_exit(struct hda_codec *codec)
{
	struct ca0132_spec *spec = codec->spec;
	unsigned int i;

	for (i = 0; i < 4; i++)
		writeb(0x0, spec->mem_base + 0x100);
	for (i = 0; i < 8; i++)
		writeb(0xb3, spec->mem_base + 0x304);

	ca0113_mmio_gpio_set(codec, 0, false);
	ca0113_mmio_gpio_set(codec, 1, false);
	ca0113_mmio_gpio_set(codec, 4, true);
	ca0113_mmio_gpio_set(codec, 5, false);
	ca0113_mmio_gpio_set(codec, 7, false);
}