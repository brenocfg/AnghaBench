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
typedef  unsigned char u8 ;
typedef  int u16 ;
struct i2c_msg {unsigned char* buf; int len; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  addr; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int reg_write(struct i2c_client *client, const u16 addr, const u8 data)
{
	struct i2c_adapter *adap = client->adapter;
	struct i2c_msg msg;
	unsigned char tx[3];
	int ret;

	msg.addr = client->addr;
	msg.buf = tx;
	msg.len = 3;
	msg.flags = 0;

	tx[0] = addr >> 8;
	tx[1] = addr & 0xff;
	tx[2] = data;

	ret = i2c_transfer(adap, &msg, 1);

	mdelay(2);

	return ret == 1 ? 0 : -EIO;
}