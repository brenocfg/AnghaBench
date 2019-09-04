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
typedef  int /*<<< orphan*/  val ;
typedef  int u8 ;
struct i2c_msg {int* buf; int len; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
struct bq2415x_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  reg ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct i2c_msg*) ; 
 int ENODEV ; 
 scalar_t__ I2C_M_RD ; 
 int /*<<< orphan*/  bq2415x_i2c_mutex ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bq2415x_i2c_read(struct bq2415x_device *bq, u8 reg)
{
	struct i2c_client *client = to_i2c_client(bq->dev);
	struct i2c_msg msg[2];
	u8 val;
	int ret;

	if (!client->adapter)
		return -ENODEV;

	msg[0].addr = client->addr;
	msg[0].flags = 0;
	msg[0].buf = &reg;
	msg[0].len = sizeof(reg);
	msg[1].addr = client->addr;
	msg[1].flags = I2C_M_RD;
	msg[1].buf = &val;
	msg[1].len = sizeof(val);

	mutex_lock(&bq2415x_i2c_mutex);
	ret = i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg));
	mutex_unlock(&bq2415x_i2c_mutex);

	if (ret < 0)
		return ret;

	return val;
}