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
 int /*<<< orphan*/  local_irq_restore (int /*<<< orphan*/ ) ; 

void DWC_SPINUNLOCK_IRQRESTORE(dwc_spinlock_t *lock, dwc_irqflags_t flags)
{
#if defined(CONFIG_PREEMPT) || defined(CONFIG_SMP)
	spin_unlock_irqrestore((spinlock_t *)lock, flags);
#else
	local_irq_restore(flags);
#endif
}