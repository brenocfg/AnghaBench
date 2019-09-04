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
typedef  int u32 ;
struct rapl_package {int power_limit_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_PACKAGE_THERM_INTERRUPT ; 
 int PACKAGE_PLN_INT_SAVED ; 
 int PACKAGE_THERM_INT_PLN_ENABLE ; 
 int /*<<< orphan*/  rdmsr_safe (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  wrmsr_safe (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void power_limit_irq_save_cpu(void *info)
{
	u32 l, h = 0;
	struct rapl_package *rp = (struct rapl_package *)info;

	/* save the state of PLN irq mask bit before disabling it */
	rdmsr_safe(MSR_IA32_PACKAGE_THERM_INTERRUPT, &l, &h);
	if (!(rp->power_limit_irq & PACKAGE_PLN_INT_SAVED)) {
		rp->power_limit_irq = l & PACKAGE_THERM_INT_PLN_ENABLE;
		rp->power_limit_irq |= PACKAGE_PLN_INT_SAVED;
	}
	l &= ~PACKAGE_THERM_INT_PLN_ENABLE;
	wrmsr_safe(MSR_IA32_PACKAGE_THERM_INTERRUPT, l, h);
}