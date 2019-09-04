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
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned short be16_to_cpu (unsigned short) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_master_recv (struct i2c_client*,char*,int) ; 

__attribute__((used)) static int ad5398_read_reg(struct i2c_client *client, unsigned short *data)
{
	unsigned short val;
	int ret;

	ret = i2c_master_recv(client, (char *)&val, 2);
	if (ret < 0) {
		dev_err(&client->dev, "I2C read error\n");
		return ret;
	}
	*data = be16_to_cpu(val);

	return ret;
}