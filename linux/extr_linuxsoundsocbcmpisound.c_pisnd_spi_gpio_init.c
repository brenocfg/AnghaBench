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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_ASIS ; 
 void* data_available ; 
 int /*<<< orphan*/  gpiod_direction_input (void*) ; 
 int /*<<< orphan*/  gpiod_direction_output (void*,int) ; 
 void* gpiod_get_index (struct device*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (void*,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 void* spi_reset ; 

__attribute__((used)) static int pisnd_spi_gpio_init(struct device *dev)
{
	spi_reset = gpiod_get_index(dev, "reset", 1, GPIOD_ASIS);
	data_available = gpiod_get_index(dev, "data_available", 0, GPIOD_ASIS);

	gpiod_direction_output(spi_reset, 1);
	gpiod_direction_input(data_available);

	/* Reset the slave. */
	gpiod_set_value(spi_reset, false);
	mdelay(1);
	gpiod_set_value(spi_reset, true);

	/* Give time for spi slave to start. */
	mdelay(64);

	return 0;
}