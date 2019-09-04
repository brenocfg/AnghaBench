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
typedef  int const u8 ;
typedef  int u16 ;
struct i2c_msg {int len; int const* buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  addr; int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct i2c_msg*) ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int const,int /*<<< orphan*/ ) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reg_read(struct i2c_client *client, const u16 addr)
{
	u8 buf[2] = {addr >> 8, addr & 0xff};
	int ret;
	struct i2c_msg msgs[] = {
		{
			.addr  = client->addr,
			.flags = 0,
			.len   = 2,
			.buf   = buf,
		}, {
			.addr  = client->addr,
			.flags = I2C_M_RD,
			.len   = 2,
			.buf   = buf,
		},
	};

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	if (ret < 0) {
		dev_warn(&client->dev, "Reading register %x from %x failed\n",
			 addr, client->addr);
		return ret;
	}

	return buf[0] & 0xff; /* no sign-extension */
}