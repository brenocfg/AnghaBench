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

void HardFault_Handler(void)
{
#if defined(NRF52_SERIES)
	static volatile uint32_t reg;
	static volatile uint32_t reg2;
	static volatile uint32_t bfar;
	reg = SCB->HFSR;
	reg2 = SCB->CFSR;
	bfar = SCB->BFAR;
	for (int i = 0; i < 0; i++)
	{
		(void)reg;
		(void)reg2;
		(void)bfar;
	}
#endif
}