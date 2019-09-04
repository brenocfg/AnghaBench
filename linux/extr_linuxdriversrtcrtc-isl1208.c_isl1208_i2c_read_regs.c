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
struct i2c_msg {int len; scalar_t__* buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  reg_addr ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 scalar_t__ ISL1219_REG_YRT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int
isl1208_i2c_read_regs(struct i2c_client *client, u8 reg, u8 buf[],
		      unsigned len)
{
	u8 reg_addr[1] = { reg };
	struct i2c_msg msgs[2] = {
		{
			.addr = client->addr,
			.len = sizeof(reg_addr),
			.buf = reg_addr
		},
		{
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = len,
			.buf = buf
		}
	};
	int ret;

	WARN_ON(reg > ISL1219_REG_YRT);
	WARN_ON(reg + len > ISL1219_REG_YRT + 1);

	ret = i2c_transfer(client->adapter, msgs, 2);
	if (ret > 0)
		ret = 0;
	return ret;
}