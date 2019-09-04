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
 scalar_t__ WDTO ; 
 int /*<<< orphan*/  outb_p (char,scalar_t__) ; 
 scalar_t__ swc_base_addr ; 

__attribute__((used)) static inline void pc87413_programm_wdto(char pc87413_time)
{
	/* Step 5: Programm WDTO, Twd. */
	outb_p(pc87413_time, swc_base_addr + WDTO);
#ifdef DEBUG
	pr_info(DPFX "Set WDTO to %d minutes\n", pc87413_time);
#endif
}