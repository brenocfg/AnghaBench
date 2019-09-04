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
 void* GPIO_DATA_DIRECTION_SM750LE ; 
 void* GPIO_DATA_SM750LE ; 
 unsigned char sw_i2c_clk_gpio ; 
 void* sw_i2c_clk_gpio_data_dir_reg ; 
 void* sw_i2c_clk_gpio_data_reg ; 
 unsigned char sw_i2c_data_gpio ; 
 void* sw_i2c_data_gpio_data_dir_reg ; 
 void* sw_i2c_data_gpio_data_reg ; 
 int /*<<< orphan*/  sw_i2c_stop () ; 

__attribute__((used)) static long sm750le_i2c_init(unsigned char clk_gpio, unsigned char data_gpio)
{
	int i;

	/* Initialize the GPIO pin for the i2c Clock Register */
	sw_i2c_clk_gpio_data_reg = GPIO_DATA_SM750LE;
	sw_i2c_clk_gpio_data_dir_reg = GPIO_DATA_DIRECTION_SM750LE;

	/* Initialize the Clock GPIO Offset */
	sw_i2c_clk_gpio = clk_gpio;

	/* Initialize the GPIO pin for the i2c Data Register */
	sw_i2c_data_gpio_data_reg = GPIO_DATA_SM750LE;
	sw_i2c_data_gpio_data_dir_reg = GPIO_DATA_DIRECTION_SM750LE;

	/* Initialize the Data GPIO Offset */
	sw_i2c_data_gpio = data_gpio;

	/* Note that SM750LE don't have GPIO MUX and power is always on */

	/* Clear the i2c lines. */
	for (i = 0; i < 9; i++)
		sw_i2c_stop();

	return 0;
}