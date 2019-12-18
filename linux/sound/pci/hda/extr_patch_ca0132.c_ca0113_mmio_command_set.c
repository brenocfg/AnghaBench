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
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void ca0113_mmio_command_set(struct hda_codec *codec, unsigned int group,
		unsigned int target, unsigned int value)
{
	struct ca0132_spec *spec = codec->spec;
	unsigned int write_val;

	writel(0x0000007e, spec->mem_base + 0x210);
	readl(spec->mem_base + 0x210);
	writel(0x0000005a, spec->mem_base + 0x210);
	readl(spec->mem_base + 0x210);
	readl(spec->mem_base + 0x210);

	writel(0x00800005, spec->mem_base + 0x20c);
	writel(group, spec->mem_base + 0x804);

	writel(0x00800005, spec->mem_base + 0x20c);
	write_val = (target & 0xff);
	write_val |= (value << 8);


	writel(write_val, spec->mem_base + 0x204);
	/*
	 * Need delay here or else it goes too fast and works inconsistently.
	 */
	msleep(20);

	readl(spec->mem_base + 0x860);
	readl(spec->mem_base + 0x854);
	readl(spec->mem_base + 0x840);

	writel(0x00800004, spec->mem_base + 0x20c);
	writel(0x00000000, spec->mem_base + 0x210);
	readl(spec->mem_base + 0x210);
	readl(spec->mem_base + 0x210);
}