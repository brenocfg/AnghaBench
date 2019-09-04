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

/* Variables and functions */
 int /*<<< orphan*/  WDT_DATA_IO_PORT ; 
 int /*<<< orphan*/  WDT_INDEX_IO_PORT ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 unsigned char swc_base_addr ; 

__attribute__((used)) static void pc87413_get_swc_base_addr(void)
{
	unsigned char addr_l, addr_h = 0;

	/* Step 3: Read SWC I/O Base Address */

	outb_p(0x60, WDT_INDEX_IO_PORT);	/* Read Index 0x60 */
	addr_h = inb(WDT_DATA_IO_PORT);

	outb_p(0x61, WDT_INDEX_IO_PORT);	/* Read Index 0x61 */

	addr_l = inb(WDT_DATA_IO_PORT);

	swc_base_addr = (addr_h << 8) + addr_l;
#ifdef DEBUG
	pr_info(DPFX
		"Read SWC I/O Base Address: low %d, high %d, res %d\n",
						addr_l, addr_h, swc_base_addr);
#endif
}