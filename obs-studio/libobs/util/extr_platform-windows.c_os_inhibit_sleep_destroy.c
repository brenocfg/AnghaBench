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
typedef  int /*<<< orphan*/  os_inhibit_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_inhibit_sleep_set_active (int /*<<< orphan*/ *,int) ; 

void os_inhibit_sleep_destroy(os_inhibit_t *info)
{
	if (info) {
		os_inhibit_sleep_set_active(info, false);
		bfree(info);
	}
}