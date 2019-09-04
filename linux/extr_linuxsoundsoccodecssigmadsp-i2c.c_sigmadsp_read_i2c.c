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
typedef  int /*<<< orphan*/  uint8_t ;
struct i2c_msg {int len; scalar_t__ flags; int /*<<< orphan*/ * buf; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ARRAY_SIZE (struct i2c_msg*) ; 
 int EIO ; 
 scalar_t__ I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  put_unaligned_be16 (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sigmadsp_read_i2c(void *control_data,
	unsigned int addr, uint8_t data[], size_t len)
{
	struct i2c_client *client = control_data;
	struct i2c_msg msgs[2];
	uint8_t buf[2];
	int ret;

	put_unaligned_be16(addr, buf);

	msgs[0].addr = client->addr;
	msgs[0].len = sizeof(buf);
	msgs[0].buf = buf;
	msgs[0].flags = 0;

	msgs[1].addr = client->addr;
	msgs[1].len = len;
	msgs[1].buf = data;
	msgs[1].flags = I2C_M_RD;

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	if (ret < 0)
		return ret;
	else if (ret != ARRAY_SIZE(msgs))
		return -EIO;
	return 0;
}