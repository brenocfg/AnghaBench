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
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 
 scalar_t__ swc_base_addr ; 

__attribute__((used)) static inline void pc87413_swc_bank3(void)
{
	/* Step 4: Select Bank3 of SWC */
	outb_p(inb(swc_base_addr + 0x0f) | 0x03, swc_base_addr + 0x0f);
#ifdef DEBUG
	pr_info(DPFX "Select Bank3 of SWC\n");
#endif
}