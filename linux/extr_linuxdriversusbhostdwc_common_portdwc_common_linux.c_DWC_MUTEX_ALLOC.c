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
struct mutex {int dummy; } ;
typedef  int /*<<< orphan*/  dwc_mutex_t ;

/* Variables and functions */
 scalar_t__ DWC_ALLOC (int) ; 
 int /*<<< orphan*/  DWC_ERROR (char*) ; 
 int /*<<< orphan*/  mutex_init (struct mutex*) ; 

dwc_mutex_t *DWC_MUTEX_ALLOC(void)
{
	struct mutex *m;
	dwc_mutex_t *mutex = (dwc_mutex_t *)DWC_ALLOC(sizeof(struct mutex));

	if (!mutex) {
		DWC_ERROR("Cannot allocate memory for mutex\n");
		return NULL;
	}

	m = (struct mutex *)mutex;
	mutex_init(m);
	return mutex;
}