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
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  u8 ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  reg ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct i2c_msg*) ; 
 scalar_t__ I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcf8523_read(struct i2c_client *client, u8 reg, u8 *valuep)
{
	struct i2c_msg msgs[2];
	u8 value = 0;
	int err;

	msgs[0].addr = client->addr;
	msgs[0].flags = 0;
	msgs[0].len = sizeof(reg);
	msgs[0].buf = &reg;

	msgs[1].addr = client->addr;
	msgs[1].flags = I2C_M_RD;
	msgs[1].len = sizeof(value);
	msgs[1].buf = &value;

	err = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	if (err < 0)
		return err;

	*valuep = value;

	return 0;
}