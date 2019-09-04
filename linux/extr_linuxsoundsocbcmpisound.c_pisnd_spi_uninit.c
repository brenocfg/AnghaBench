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
 int /*<<< orphan*/ * pisnd_spi_device ; 
 int /*<<< orphan*/  pisnd_spi_gpio_irq_uninit () ; 
 int /*<<< orphan*/  pisnd_spi_gpio_uninit () ; 
 int /*<<< orphan*/  pisnd_uninit_workqueues () ; 
 int /*<<< orphan*/  spi_dev_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pisnd_spi_uninit(void)
{
	pisnd_uninit_workqueues();

	spi_dev_put(pisnd_spi_device);
	pisnd_spi_device = NULL;

	pisnd_spi_gpio_irq_uninit();
	pisnd_spi_gpio_uninit();
}