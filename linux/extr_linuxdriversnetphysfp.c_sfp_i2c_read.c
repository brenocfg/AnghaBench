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
typedef  void* u8 ;
struct sfp {int /*<<< orphan*/  i2c; } ;
struct i2c_msg {int len; void** buf; scalar_t__ flags; void* addr; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct i2c_msg*) ; 
 scalar_t__ I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int sfp_i2c_read(struct sfp *sfp, bool a2, u8 dev_addr, void *buf,
			size_t len)
{
	struct i2c_msg msgs[2];
	u8 bus_addr = a2 ? 0x51 : 0x50;
	int ret;

	msgs[0].addr = bus_addr;
	msgs[0].flags = 0;
	msgs[0].len = 1;
	msgs[0].buf = &dev_addr;
	msgs[1].addr = bus_addr;
	msgs[1].flags = I2C_M_RD;
	msgs[1].len = len;
	msgs[1].buf = buf;

	ret = i2c_transfer(sfp->i2c, msgs, ARRAY_SIZE(msgs));
	if (ret < 0)
		return ret;

	return ret == ARRAY_SIZE(msgs) ? len : 0;
}