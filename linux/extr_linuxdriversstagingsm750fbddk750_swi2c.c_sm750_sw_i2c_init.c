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
 void* GPIO_DATA ; 
 void* GPIO_DATA_DIRECTION ; 
 int /*<<< orphan*/  GPIO_MUX ; 
 scalar_t__ SM750LE ; 
 int peek32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poke32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sm750_enable_gpio (int) ; 
 scalar_t__ sm750_get_chip_type () ; 
 long sm750le_i2c_init (unsigned char,unsigned char) ; 
 int sw_i2c_clk_gpio ; 
 void* sw_i2c_clk_gpio_data_dir_reg ; 
 void* sw_i2c_clk_gpio_data_reg ; 
 int /*<<< orphan*/  sw_i2c_clk_gpio_mux_reg ; 
 int sw_i2c_data_gpio ; 
 void* sw_i2c_data_gpio_data_dir_reg ; 
 void* sw_i2c_data_gpio_data_reg ; 
 int /*<<< orphan*/  sw_i2c_data_gpio_mux_reg ; 
 int /*<<< orphan*/  sw_i2c_stop () ; 

long sm750_sw_i2c_init(unsigned char clk_gpio, unsigned char data_gpio)
{
	int i;

	/*
	 * Return 0 if the GPIO pins to be used is out of range. The
	 * range is only from [0..63]
	 */
	if ((clk_gpio > 31) || (data_gpio > 31))
		return -1;

	if (sm750_get_chip_type() == SM750LE)
		return sm750le_i2c_init(clk_gpio, data_gpio);

	/* Initialize the GPIO pin for the i2c Clock Register */
	sw_i2c_clk_gpio_mux_reg = GPIO_MUX;
	sw_i2c_clk_gpio_data_reg = GPIO_DATA;
	sw_i2c_clk_gpio_data_dir_reg = GPIO_DATA_DIRECTION;

	/* Initialize the Clock GPIO Offset */
	sw_i2c_clk_gpio = clk_gpio;

	/* Initialize the GPIO pin for the i2c Data Register */
	sw_i2c_data_gpio_mux_reg = GPIO_MUX;
	sw_i2c_data_gpio_data_reg = GPIO_DATA;
	sw_i2c_data_gpio_data_dir_reg = GPIO_DATA_DIRECTION;

	/* Initialize the Data GPIO Offset */
	sw_i2c_data_gpio = data_gpio;

	/* Enable the GPIO pins for the i2c Clock and Data (GPIO MUX) */
	poke32(sw_i2c_clk_gpio_mux_reg,
	       peek32(sw_i2c_clk_gpio_mux_reg) & ~(1 << sw_i2c_clk_gpio));
	poke32(sw_i2c_data_gpio_mux_reg,
	       peek32(sw_i2c_data_gpio_mux_reg) & ~(1 << sw_i2c_data_gpio));

	/* Enable GPIO power */
	sm750_enable_gpio(1);

	/* Clear the i2c lines. */
	for (i = 0; i < 9; i++)
		sw_i2c_stop();

	return 0;
}