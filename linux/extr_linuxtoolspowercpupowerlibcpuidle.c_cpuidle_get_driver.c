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
 int /*<<< orphan*/  CPUIDLE_DRIVER ; 
 char* sysfs_cpuidle_get_one_string (int /*<<< orphan*/ ) ; 

char *cpuidle_get_driver(void)
{
	return sysfs_cpuidle_get_one_string(CPUIDLE_DRIVER);
}