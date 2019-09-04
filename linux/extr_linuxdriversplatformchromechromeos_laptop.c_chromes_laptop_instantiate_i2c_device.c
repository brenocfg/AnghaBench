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
struct i2c_client {int /*<<< orphan*/  addr; } ;
struct i2c_board_info {unsigned short const addr; int /*<<< orphan*/  member_0; } ;
struct i2c_adapter {int /*<<< orphan*/  nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_BOARD_INFO (char*,unsigned short const) ; 
 unsigned short const I2C_CLIENT_END ; 
 struct i2c_client* i2c_new_device (struct i2c_adapter*,struct i2c_board_info*) ; 
 struct i2c_client* i2c_new_probed_device (struct i2c_adapter*,struct i2c_board_info*,unsigned short const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,unsigned short const,...) ; 

__attribute__((used)) static struct i2c_client *
chromes_laptop_instantiate_i2c_device(struct i2c_adapter *adapter,
				      struct i2c_board_info *info,
				      unsigned short alt_addr)
{
	const unsigned short addr_list[] = { info->addr, I2C_CLIENT_END };
	struct i2c_client *client;

	/*
	 * Add the i2c device. If we can't detect it at the primary
	 * address we scan secondary addresses. In any case the client
	 * structure gets assigned primary address.
	 */
	client = i2c_new_probed_device(adapter, info, addr_list, NULL);
	if (!client && alt_addr) {
		struct i2c_board_info dummy_info = {
			I2C_BOARD_INFO("dummy", info->addr),
		};
		const unsigned short alt_addr_list[] = {
			alt_addr, I2C_CLIENT_END
		};
		struct i2c_client *dummy;

		dummy = i2c_new_probed_device(adapter, &dummy_info,
					      alt_addr_list, NULL);
		if (dummy) {
			pr_debug("%d-%02x is probed at %02x\n",
				 adapter->nr, info->addr, dummy->addr);
			i2c_unregister_device(dummy);
			client = i2c_new_device(adapter, info);
		}
	}

	if (!client)
		pr_debug("failed to register device %d-%02x\n",
			 adapter->nr, info->addr);
	else
		pr_debug("added i2c device %d-%02x\n",
			 adapter->nr, info->addr);

	return client;
}