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
typedef  int u8 ;
typedef  int u16 ;
struct watchdog_device {int /*<<< orphan*/  parent; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  ZIIRAVE_CMD_DOWNLOAD_SET_READ_ADDR ; 
 int i2c_smbus_write_block_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ziirave_firm_set_read_addr(struct watchdog_device *wdd, u16 addr)
{
	struct i2c_client *client = to_i2c_client(wdd->parent);
	u8 address[2];

	address[0] = addr & 0xff;
	address[1] = (addr >> 8) & 0xff;

	return i2c_smbus_write_block_data(client,
					  ZIIRAVE_CMD_DOWNLOAD_SET_READ_ADDR,
					  ARRAY_SIZE(address), address);
}