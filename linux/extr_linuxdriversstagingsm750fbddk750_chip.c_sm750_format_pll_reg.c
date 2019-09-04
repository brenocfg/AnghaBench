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
struct pll_value {unsigned int POD; unsigned int OD; unsigned int M; unsigned int N; } ;

/* Variables and functions */
 unsigned int PLL_CTRL_M_MASK ; 
 unsigned int PLL_CTRL_M_SHIFT ; 
 unsigned int PLL_CTRL_N_MASK ; 
 unsigned int PLL_CTRL_N_SHIFT ; 
 unsigned int PLL_CTRL_OD_MASK ; 
 unsigned int PLL_CTRL_OD_SHIFT ; 
 unsigned int PLL_CTRL_POD_MASK ; 
 unsigned int PLL_CTRL_POD_SHIFT ; 
 unsigned int PLL_CTRL_POWER ; 

unsigned int sm750_format_pll_reg(struct pll_value *pPLL)
{
#ifndef VALIDATION_CHIP
	unsigned int POD = pPLL->POD;
#endif
	unsigned int OD = pPLL->OD;
	unsigned int M = pPLL->M;
	unsigned int N = pPLL->N;
	unsigned int reg = 0;

	/*
	 * Note that all PLL's have the same format. Here, we just use
	 * Panel PLL parameter to work out the bit fields in the
	 * register. On returning a 32 bit number, the value can be
	 * applied to any PLL in the calling function.
	 */
	reg = PLL_CTRL_POWER |
#ifndef VALIDATION_CHIP
		((POD << PLL_CTRL_POD_SHIFT) & PLL_CTRL_POD_MASK) |
#endif
		((OD << PLL_CTRL_OD_SHIFT) & PLL_CTRL_OD_MASK) |
		((N << PLL_CTRL_N_SHIFT) & PLL_CTRL_N_MASK) |
		((M << PLL_CTRL_M_SHIFT) & PLL_CTRL_M_MASK);

	return reg;
}