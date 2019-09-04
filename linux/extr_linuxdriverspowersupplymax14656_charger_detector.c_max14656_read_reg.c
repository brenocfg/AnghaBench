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
typedef  scalar_t__ u8 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,scalar_t__) ; 
 scalar_t__ i2c_smbus_read_byte_data (struct i2c_client*,int) ; 

__attribute__((used)) static int max14656_read_reg(struct i2c_client *client, int reg, u8 *val)
{
	s32 ret;

	ret = i2c_smbus_read_byte_data(client, reg);
	if (ret < 0) {
		dev_err(&client->dev,
			"i2c read fail: can't read from %02x: %d\n",
			reg, ret);
		return ret;
	}
	*val = ret;
	return 0;
}