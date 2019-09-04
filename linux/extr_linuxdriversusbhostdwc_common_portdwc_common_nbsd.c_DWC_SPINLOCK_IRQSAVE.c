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
struct simplelock {int dummy; } ;
typedef  int /*<<< orphan*/  dwc_spinlock_t ;
typedef  int /*<<< orphan*/  dwc_irqflags_t ;

/* Variables and functions */
 int /*<<< orphan*/  simple_lock (struct simplelock*) ; 
 int /*<<< orphan*/  splbio () ; 

void DWC_SPINLOCK_IRQSAVE(dwc_spinlock_t *lock, dwc_irqflags_t *flags)
{
	simple_lock((struct simplelock *)lock);
	*flags = splbio();
}