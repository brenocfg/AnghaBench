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
typedef  int /*<<< orphan*/  u8 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  int s32 ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 int RV8803_I2C_TRY_COUNT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rv8803_read_reg(const struct i2c_client *client, u8 reg)
{
	int try = RV8803_I2C_TRY_COUNT;
	s32 ret;

	/*
	 * There is a 61µs window during which the RTC does not acknowledge I2C
	 * transfers. In that case, ensure that there are multiple attempts.
	 */
	do
		ret = i2c_smbus_read_byte_data(client, reg);
	while ((ret == -ENXIO || ret == -EIO) && --try);
	if (ret < 0)
		dev_err(&client->dev, "Unable to read register 0x%02x\n", reg);

	return ret;
}