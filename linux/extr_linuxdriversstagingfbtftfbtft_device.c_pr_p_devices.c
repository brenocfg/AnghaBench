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
 int /*<<< orphan*/  bus_for_each_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_device_found ; 
 int /*<<< orphan*/  platform_bus_type ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static void pr_p_devices(void)
{
	pr_debug("'fb' Platform devices registered:\n");
	bus_for_each_dev(&platform_bus_type, NULL, NULL, p_device_found);
}