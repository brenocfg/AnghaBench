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
typedef  int /*<<< orphan*/  u8 ;
struct watchdog_device {int /*<<< orphan*/  parent; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int i2c_smbus_write_block_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 
 int ziirave_firm_wait_for_ack (struct watchdog_device*) ; 

__attribute__((used)) static int ziirave_firm_write_block_data(struct watchdog_device *wdd,
					 u8 command, u8 length, const u8 *data,
					 bool wait_for_ack)
{
	struct i2c_client *client = to_i2c_client(wdd->parent);
	int ret;

	ret = i2c_smbus_write_block_data(client, command, length, data);
	if (ret) {
		dev_err(&client->dev,
			"Failed to send command 0x%02x: %d\n", command, ret);
		return ret;
	}

	if (wait_for_ack)
		ret = ziirave_firm_wait_for_ack(wdd);

	return ret;
}