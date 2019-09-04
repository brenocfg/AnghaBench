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
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  spi_bus_type ; 
 int /*<<< orphan*/  spi_device_found ; 

__attribute__((used)) static void pr_spi_devices(void)
{
	pr_debug("SPI devices registered:\n");
	bus_for_each_dev(&spi_bus_type, NULL, NULL, spi_device_found);
}