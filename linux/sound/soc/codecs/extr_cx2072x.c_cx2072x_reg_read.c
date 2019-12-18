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
struct i2c_msg {int len; unsigned int* buf; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; struct device dev; } ;
typedef  int /*<<< orphan*/  send_buf ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 int ARRAY_SIZE (struct i2c_msg*) ; 
 int EIO ; 
 scalar_t__ I2C_M_RD ; 
 unsigned int cx2072x_register_size (unsigned int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 unsigned int le32_to_cpu (scalar_t__) ; 

__attribute__((used)) static int cx2072x_reg_read(void *context, unsigned int reg,
			    unsigned int *value)
{
	struct i2c_client *client = context;
	struct device *dev = &client->dev;
	__le32 recv_buf = 0;
	struct i2c_msg msgs[2];
	unsigned int size;
	u8 send_buf[2];
	int ret;

	size = cx2072x_register_size(reg);

	send_buf[0] = reg >> 8;
	send_buf[1] = reg & 0xff;

	msgs[0].addr = client->addr;
	msgs[0].len = sizeof(send_buf);
	msgs[0].buf = send_buf;
	msgs[0].flags = 0;

	msgs[1].addr = client->addr;
	msgs[1].len = size;
	msgs[1].buf = (u8 *)&recv_buf;
	msgs[1].flags = I2C_M_RD;

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	if (ret != ARRAY_SIZE(msgs)) {
		dev_err(dev, "Failed to read register, ret = %d\n", ret);
		return ret < 0 ? ret : -EIO;
	}

	*value = le32_to_cpu(recv_buf);
	return 0;
}