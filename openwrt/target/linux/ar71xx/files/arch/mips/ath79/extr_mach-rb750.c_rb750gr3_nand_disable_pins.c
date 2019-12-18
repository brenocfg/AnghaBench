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
 int /*<<< orphan*/  AR724X_GPIO_FUNC_JTAG_DISABLE ; 
 int AR724X_GPIO_FUNC_SPI_CS_EN2 ; 
 int AR724X_GPIO_FUNC_SPI_EN ; 
 int /*<<< orphan*/  ath79_gpio_function_setup (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rb750gr3_nand_disable_pins(void)
{
	ath79_gpio_function_setup(AR724X_GPIO_FUNC_SPI_EN |
				  AR724X_GPIO_FUNC_SPI_CS_EN2,
				  AR724X_GPIO_FUNC_JTAG_DISABLE);
}