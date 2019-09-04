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

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PCF85063_REG_CTRL1 ; 
 int /*<<< orphan*/  PCF85063_REG_CTRL1_STOP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcf85063_start_clock(struct i2c_client *client, u8 ctrl1)
{
	int rc;

	/* start the clock */
	ctrl1 &= ~PCF85063_REG_CTRL1_STOP;

	rc = i2c_smbus_write_byte_data(client, PCF85063_REG_CTRL1, ctrl1);
	if (rc < 0) {
		dev_err(&client->dev, "Failing to start the clock\n");
		return -EIO;
	}

	return 0;
}