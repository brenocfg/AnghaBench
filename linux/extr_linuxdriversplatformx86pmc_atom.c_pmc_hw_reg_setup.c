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
typedef  int /*<<< orphan*/  u32 ;
struct pmc_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMC_S0IX_WAKE_EN ; 
 scalar_t__ PMC_WAKE_EN_SETTING ; 
 int /*<<< orphan*/  pmc_reg_write (struct pmc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pmc_hw_reg_setup(struct pmc_dev *pmc)
{
	/*
	 * Disable PMC S0IX_WAKE_EN events coming from:
	 * - LPC clock run
	 * - GPIO_SUS ored dedicated IRQs
	 * - GPIO_SCORE ored dedicated IRQs
	 * - GPIO_SUS shared IRQ
	 * - GPIO_SCORE shared IRQ
	 */
	pmc_reg_write(pmc, PMC_S0IX_WAKE_EN, (u32)PMC_WAKE_EN_SETTING);
}