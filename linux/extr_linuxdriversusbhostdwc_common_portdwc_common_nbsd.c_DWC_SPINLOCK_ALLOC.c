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

/* Variables and functions */
 struct simplelock* DWC_ALLOC (int) ; 
 int /*<<< orphan*/  DWC_ERROR (char*) ; 
 int /*<<< orphan*/  simple_lock_init (struct simplelock*) ; 

dwc_spinlock_t *DWC_SPINLOCK_ALLOC(void)
{
	struct simplelock *sl = DWC_ALLOC(sizeof(*sl));

	if (!sl) {
		DWC_ERROR("Cannot allocate memory for spinlock");
		return NULL;
	}

	simple_lock_init(sl);
	return (dwc_spinlock_t *)sl;
}