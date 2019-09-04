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
struct bcm2048_device {struct i2c_client* client; int /*<<< orphan*/  power_state; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2c_smbus_read_byte_data (struct i2c_client*,unsigned int) ; 

__attribute__((used)) static int bcm2048_recv_command(struct bcm2048_device *bdev, unsigned int reg,
				u8 *value)
{
	struct i2c_client *client = bdev->client;

	if (!bdev->power_state) {
		dev_err(&bdev->client->dev, "bcm2048: chip not powered!\n");
		return -EIO;
	}

	value[0] = i2c_smbus_read_byte_data(client, reg & 0xff);

	return 0;
}