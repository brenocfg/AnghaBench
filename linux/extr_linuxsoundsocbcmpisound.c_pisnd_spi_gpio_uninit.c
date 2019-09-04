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
 int /*<<< orphan*/ * data_available ; 
 int /*<<< orphan*/  gpiod_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * spi_reset ; 

__attribute__((used)) static void pisnd_spi_gpio_uninit(void)
{
	gpiod_set_value(spi_reset, false);
	gpiod_put(spi_reset);
	spi_reset = NULL;

	gpiod_put(data_available);
	data_available = NULL;
}