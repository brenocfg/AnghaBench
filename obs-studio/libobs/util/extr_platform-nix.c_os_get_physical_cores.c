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

/* Variables and functions */
 int /*<<< orphan*/  core_count_initialized ; 
 int /*<<< orphan*/  os_get_cores_internal () ; 
 int physical_cores ; 

int os_get_physical_cores(void)
{
	if (!core_count_initialized)
		os_get_cores_internal();
	return physical_cores;
}