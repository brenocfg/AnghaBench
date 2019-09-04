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
typedef  int u8 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ABX8XX_CFG_KEY_MISC ; 
 int /*<<< orphan*/  ABX8XX_REG_CFG_KEY ; 
 int /*<<< orphan*/  ABX8XX_REG_TRICKLE ; 
 int ABX8XX_TRICKLE_CHARGE_ENABLE ; 
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int abx80x_enable_trickle_charger(struct i2c_client *client,
					 u8 trickle_cfg)
{
	int err;

	/*
	 * Write the configuration key register to enable access to the Trickle
	 * register
	 */
	err = i2c_smbus_write_byte_data(client, ABX8XX_REG_CFG_KEY,
					ABX8XX_CFG_KEY_MISC);
	if (err < 0) {
		dev_err(&client->dev, "Unable to write configuration key\n");
		return -EIO;
	}

	err = i2c_smbus_write_byte_data(client, ABX8XX_REG_TRICKLE,
					ABX8XX_TRICKLE_CHARGE_ENABLE |
					trickle_cfg);
	if (err < 0) {
		dev_err(&client->dev, "Unable to write trickle register\n");
		return -EIO;
	}

	return 0;
}