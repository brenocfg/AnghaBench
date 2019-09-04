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
struct rtc_mem {int nr; unsigned char* data; int loc; } ;
struct i2c_msg {int len; unsigned char* buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int pcf8583_read_mem(struct i2c_client *client, struct rtc_mem *mem)
{
	unsigned char addr[1];
	struct i2c_msg msgs[2] = {
		{
			.addr = client->addr,
			.flags = 0,
			.len = 1,
			.buf = addr,
		}, {
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = mem->nr,
			.buf = mem->data,
		}
	};

	if (mem->loc < 8)
		return -EINVAL;

	addr[0] = mem->loc;

	return i2c_transfer(client->adapter, msgs, 2) == 2 ? 0 : -EIO;
}