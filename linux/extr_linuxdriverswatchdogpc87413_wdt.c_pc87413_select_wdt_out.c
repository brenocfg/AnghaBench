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
 unsigned int SIOCFG2 ; 
 int /*<<< orphan*/  WDT_DATA_IO_PORT ; 
 int /*<<< orphan*/  WDT_INDEX_IO_PORT ; 
 unsigned int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void pc87413_select_wdt_out(void)
{
	unsigned int cr_data = 0;

	/* Step 1: Select multiple pin,pin55,as WDT output */

	outb_p(SIOCFG2, WDT_INDEX_IO_PORT);

	cr_data = inb(WDT_DATA_IO_PORT);

	cr_data |= 0x80; /* Set Bit7 to 1*/
	outb_p(SIOCFG2, WDT_INDEX_IO_PORT);

	outb_p(cr_data, WDT_DATA_IO_PORT);

#ifdef DEBUG
	pr_info(DPFX
		"Select multiple pin,pin55,as WDT output: Bit7 to 1: %d\n",
								cr_data);
#endif
}