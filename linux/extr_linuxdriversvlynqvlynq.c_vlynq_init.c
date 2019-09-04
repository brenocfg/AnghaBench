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
 int bus_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_unregister (int /*<<< orphan*/ *) ; 
 int platform_driver_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlynq_bus_type ; 
 int /*<<< orphan*/  vlynq_platform_driver ; 

__attribute__((used)) static int vlynq_init(void)
{
	int res = 0;

	res = bus_register(&vlynq_bus_type);
	if (res)
		goto fail_bus;

	res = platform_driver_register(&vlynq_platform_driver);
	if (res)
		goto fail_platform;

	return 0;

fail_platform:
	bus_unregister(&vlynq_bus_type);
fail_bus:
	return res;
}