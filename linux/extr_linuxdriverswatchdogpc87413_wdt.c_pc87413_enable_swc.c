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
 unsigned int SWC_LDN ; 
 int /*<<< orphan*/  WDT_DATA_IO_PORT ; 
 int /*<<< orphan*/  WDT_INDEX_IO_PORT ; 
 unsigned int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void pc87413_enable_swc(void)
{
	unsigned int cr_data = 0;

	/* Step 2: Enable SWC functions */

	outb_p(0x07, WDT_INDEX_IO_PORT);	/* Point SWC_LDN (LDN=4) */
	outb_p(SWC_LDN, WDT_DATA_IO_PORT);

	outb_p(0x30, WDT_INDEX_IO_PORT);	/* Read Index 0x30 First */
	cr_data = inb(WDT_DATA_IO_PORT);
	cr_data |= 0x01;			/* Set Bit0 to 1 */
	outb_p(0x30, WDT_INDEX_IO_PORT);
	outb_p(cr_data, WDT_DATA_IO_PORT);	/* Index0x30_bit0P1 */

#ifdef DEBUG
	pr_info(DPFX "pc87413 - Enable SWC functions\n");
#endif
}