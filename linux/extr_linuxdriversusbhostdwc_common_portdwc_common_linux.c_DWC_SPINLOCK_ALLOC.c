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
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  dwc_spinlock_t ;

/* Variables and functions */

dwc_spinlock_t *DWC_SPINLOCK_ALLOC(void)
{
	spinlock_t *sl = (spinlock_t *)1;

#if defined(CONFIG_PREEMPT) || defined(CONFIG_SMP)
	sl = DWC_ALLOC(sizeof(*sl));
	if (!sl) {
		DWC_ERROR("Cannot allocate memory for spinlock\n");
		return NULL;
	}

	spin_lock_init(sl);
#endif
	return (dwc_spinlock_t *)sl;
}