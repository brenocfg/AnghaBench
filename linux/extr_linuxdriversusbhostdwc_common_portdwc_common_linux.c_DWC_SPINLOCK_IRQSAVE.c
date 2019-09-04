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
typedef  int /*<<< orphan*/  dwc_spinlock_t ;
typedef  int /*<<< orphan*/  dwc_irqflags_t ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_save (int /*<<< orphan*/ ) ; 

void DWC_SPINLOCK_IRQSAVE(dwc_spinlock_t *lock, dwc_irqflags_t *flags)
{
	dwc_irqflags_t f;

#if defined(CONFIG_PREEMPT) || defined(CONFIG_SMP)
	spin_lock_irqsave((spinlock_t *)lock, f);
#else
	local_irq_save(f);
#endif
	*flags = f;
}