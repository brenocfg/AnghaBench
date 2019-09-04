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
struct lock {int dummy; } ;
typedef  int /*<<< orphan*/  dwc_mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/ * DWC_ALLOC (int) ; 
 int /*<<< orphan*/  DWC_ERROR (char*) ; 
 int /*<<< orphan*/  lockinit (struct lock*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

dwc_mutex_t *DWC_MUTEX_ALLOC(void)
{
	dwc_mutex_t *mutex = DWC_ALLOC(sizeof(struct lock));

	if (!mutex) {
		DWC_ERROR("Cannot allocate memory for mutex");
		return NULL;
	}

	lockinit((struct lock *)mutex, 0, "dw3mtx", 0, 0);
	return mutex;
}