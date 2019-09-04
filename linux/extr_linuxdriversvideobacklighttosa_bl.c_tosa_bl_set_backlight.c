#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct tosa_bl_data {TYPE_1__* i2c; int /*<<< orphan*/  comadj; } ;
struct spi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAC_CH1 ; 
 int /*<<< orphan*/  DAC_CH2 ; 
 int /*<<< orphan*/  TOSA_GPIO_BL_C20MA ; 
 struct spi_device* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tosa_bl_enable (struct spi_device*,int) ; 

__attribute__((used)) static void tosa_bl_set_backlight(struct tosa_bl_data *data, int brightness)
{
	struct spi_device *spi = dev_get_platdata(&data->i2c->dev);

	i2c_smbus_write_byte_data(data->i2c, DAC_CH1, data->comadj);

	/* SetBacklightDuty */
	i2c_smbus_write_byte_data(data->i2c, DAC_CH2, (u8)(brightness & 0xff));

	/* SetBacklightVR */
	gpio_set_value(TOSA_GPIO_BL_C20MA, brightness & 0x100);

	tosa_bl_enable(spi, brightness);
}