#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int PMC_PCDR; } ;

/* Variables and functions */
 scalar_t__* AT91C_AIC_EOICR ; 
 int* AT91C_AIC_FVR ; 
 int* AT91C_AIC_ICCR ; 
 int* AT91C_AIC_IVR ; 
 int /*<<< orphan*/  AT91C_BASE_AIC ; 
 TYPE_1__* AT91C_BASE_PMC ; 
 int /*<<< orphan*/  AT91C_ID_SYS ; 
 int* AT91C_PIOA_ODR ; 
 int* AT91C_PIOA_PER ; 
 int /*<<< orphan*/  AT91F_AIC_DisableIt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int AT91F_ResetRegisters(void)
{
	volatile int i = 0;

	/* set the PIOs in input*/
	/* This disables the UART output, so dont execute for now*/

#ifndef	DEBUGOUT
	*AT91C_PIOA_ODR = 0xFFFFFFFF;	/* Disables all the output pins */
	*AT91C_PIOA_PER = 0xFFFFFFFF;	/* Enables the PIO to control all the pins */
#endif

	AT91F_AIC_DisableIt (AT91C_BASE_AIC, AT91C_ID_SYS);
	/* close all peripheral clocks */

#ifndef	DEBUGOUT
	AT91C_BASE_PMC->PMC_PCDR = 0xFFFFFFFC;
#endif
	/* Disable core interrupts and set supervisor mode */
	__asm__ ("msr CPSR_c, #0xDF"); //* ARM_MODE_SYS(0x1F) | I_BIT(0x80) | F_BIT(0x40)
	/* Clear all the interrupts */
	*AT91C_AIC_ICCR = 0xffffffff;

	/* read the AIC_IVR and AIC_FVR */
	i = *AT91C_AIC_IVR;
	i = *AT91C_AIC_FVR;

	/* write the end of interrupt control register */
	*AT91C_AIC_EOICR	= 0;

	return 1;
}