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
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ABX8XX_IRQ_AIE ; 
 int ABX8XX_IRQ_IM_1_4 ; 
 int /*<<< orphan*/  ABX8XX_REG_IRQ ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int abx80x_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct i2c_client *client = to_i2c_client(dev);
	int err;

	if (enabled)
		err = i2c_smbus_write_byte_data(client, ABX8XX_REG_IRQ,
						(ABX8XX_IRQ_IM_1_4 |
						 ABX8XX_IRQ_AIE));
	else
		err = i2c_smbus_write_byte_data(client, ABX8XX_REG_IRQ,
						ABX8XX_IRQ_IM_1_4);
	return err;
}