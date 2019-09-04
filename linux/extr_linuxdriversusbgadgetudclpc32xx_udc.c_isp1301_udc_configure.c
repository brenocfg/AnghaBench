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
struct lpc32xx_udc {int /*<<< orphan*/  isp1301_i2c_client; int /*<<< orphan*/  dev; TYPE_1__* board; } ;
struct TYPE_2__ {scalar_t__ vbus_drv_pol; } ;

/* Variables and functions */
 int INT_VBUS_VLD ; 
 int ISP1301_I2C_INTERRUPT_FALLING ; 
 int ISP1301_I2C_INTERRUPT_LATCH ; 
 int ISP1301_I2C_INTERRUPT_RISING ; 
 int ISP1301_I2C_MODE_CONTROL_1 ; 
 int ISP1301_I2C_MODE_CONTROL_2 ; 
 int ISP1301_I2C_OTG_CONTROL_1 ; 
 int ISP1301_I2C_REG_CLEAR_ADDR ; 
 int MC1_DAT_SE0 ; 
 int MC1_SPEED_REG ; 
 int MC1_UART_EN ; 
 int MC2_BI_DI ; 
 int MC2_SPD_SUSP_CTRL ; 
 int OTG1_DM_PULLDOWN ; 
 int OTG1_DP_PULLDOWN ; 
 int OTG1_VBUS_DISCHRG ; 
 int OTG1_VBUS_DRV ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_read_word_data (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void isp1301_udc_configure(struct lpc32xx_udc *udc)
{
	/* LPC32XX only supports DAT_SE0 USB mode */
	/* This sequence is important */

	/* Disable transparent UART mode first */
	i2c_smbus_write_byte_data(udc->isp1301_i2c_client,
		(ISP1301_I2C_MODE_CONTROL_1 | ISP1301_I2C_REG_CLEAR_ADDR),
		MC1_UART_EN);

	/* Set full speed and SE0 mode */
	i2c_smbus_write_byte_data(udc->isp1301_i2c_client,
		(ISP1301_I2C_MODE_CONTROL_1 | ISP1301_I2C_REG_CLEAR_ADDR), ~0);
	i2c_smbus_write_byte_data(udc->isp1301_i2c_client,
		ISP1301_I2C_MODE_CONTROL_1, (MC1_SPEED_REG | MC1_DAT_SE0));

	/*
	 * The PSW_OE enable bit state is reversed in the ISP1301 User's Guide
	 */
	i2c_smbus_write_byte_data(udc->isp1301_i2c_client,
		(ISP1301_I2C_MODE_CONTROL_2 | ISP1301_I2C_REG_CLEAR_ADDR), ~0);
	i2c_smbus_write_byte_data(udc->isp1301_i2c_client,
		ISP1301_I2C_MODE_CONTROL_2, (MC2_BI_DI | MC2_SPD_SUSP_CTRL));

	/* Driver VBUS_DRV high or low depending on board setup */
	if (udc->board->vbus_drv_pol != 0)
		i2c_smbus_write_byte_data(udc->isp1301_i2c_client,
			ISP1301_I2C_OTG_CONTROL_1, OTG1_VBUS_DRV);
	else
		i2c_smbus_write_byte_data(udc->isp1301_i2c_client,
			ISP1301_I2C_OTG_CONTROL_1 | ISP1301_I2C_REG_CLEAR_ADDR,
			OTG1_VBUS_DRV);

	/* Bi-directional mode with suspend control
	 * Enable both pulldowns for now - the pullup will be enable when VBUS
	 * is detected */
	i2c_smbus_write_byte_data(udc->isp1301_i2c_client,
		(ISP1301_I2C_OTG_CONTROL_1 | ISP1301_I2C_REG_CLEAR_ADDR), ~0);
	i2c_smbus_write_byte_data(udc->isp1301_i2c_client,
		ISP1301_I2C_OTG_CONTROL_1,
		(0 | OTG1_DM_PULLDOWN | OTG1_DP_PULLDOWN));

	/* Discharge VBUS (just in case) */
	i2c_smbus_write_byte_data(udc->isp1301_i2c_client,
		ISP1301_I2C_OTG_CONTROL_1, OTG1_VBUS_DISCHRG);
	msleep(1);
	i2c_smbus_write_byte_data(udc->isp1301_i2c_client,
		(ISP1301_I2C_OTG_CONTROL_1 | ISP1301_I2C_REG_CLEAR_ADDR),
		OTG1_VBUS_DISCHRG);

	/* Clear and enable VBUS high edge interrupt */
	i2c_smbus_write_byte_data(udc->isp1301_i2c_client,
		ISP1301_I2C_INTERRUPT_LATCH | ISP1301_I2C_REG_CLEAR_ADDR, ~0);
	i2c_smbus_write_byte_data(udc->isp1301_i2c_client,
		ISP1301_I2C_INTERRUPT_FALLING | ISP1301_I2C_REG_CLEAR_ADDR, ~0);
	i2c_smbus_write_byte_data(udc->isp1301_i2c_client,
		ISP1301_I2C_INTERRUPT_FALLING, INT_VBUS_VLD);
	i2c_smbus_write_byte_data(udc->isp1301_i2c_client,
		ISP1301_I2C_INTERRUPT_RISING | ISP1301_I2C_REG_CLEAR_ADDR, ~0);
	i2c_smbus_write_byte_data(udc->isp1301_i2c_client,
		ISP1301_I2C_INTERRUPT_RISING, INT_VBUS_VLD);

	dev_info(udc->dev, "ISP1301 Vendor ID  : 0x%04x\n",
		 i2c_smbus_read_word_data(udc->isp1301_i2c_client, 0x00));
	dev_info(udc->dev, "ISP1301 Product ID : 0x%04x\n",
		 i2c_smbus_read_word_data(udc->isp1301_i2c_client, 0x02));
	dev_info(udc->dev, "ISP1301 Version ID : 0x%04x\n",
		 i2c_smbus_read_word_data(udc->isp1301_i2c_client, 0x14));
}