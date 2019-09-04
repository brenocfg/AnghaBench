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
 int /*<<< orphan*/  DWC_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (struct mutex*) ; 

void DWC_MUTEX_FREE(dwc_mutex_t *mutex)
{
	mutex_destroy((struct mutex *)mutex);
	DWC_FREE(mutex);
}