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
typedef  unsigned int u8 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct bcm2048_device {struct i2c_client* client; int /*<<< orphan*/  power_state; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_master_send (struct i2c_client*,unsigned int*,int) ; 

__attribute__((used)) static int bcm2048_send_command(struct bcm2048_device *bdev, unsigned int reg,
				unsigned int value)
{
	struct i2c_client *client = bdev->client;
	u8 data[2];

	if (!bdev->power_state) {
		dev_err(&bdev->client->dev, "bcm2048: chip not powered!\n");
		return -EIO;
	}

	data[0] = reg & 0xff;
	data[1] = value & 0xff;

	if (i2c_master_send(client, data, 2) == 2)
		return 0;

	dev_err(&bdev->client->dev, "BCM I2C error!\n");
	dev_err(&bdev->client->dev, "Is Bluetooth up and running?\n");
	return -EIO;
}