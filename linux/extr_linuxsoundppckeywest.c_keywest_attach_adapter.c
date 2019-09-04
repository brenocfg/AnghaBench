#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct i2c_board_info {int /*<<< orphan*/  addr; int /*<<< orphan*/  type; } ;
struct i2c_adapter {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int /*<<< orphan*/  driver; } ;
struct TYPE_9__ {TYPE_1__ dev; int /*<<< orphan*/  detected; } ;
struct TYPE_8__ {TYPE_4__* client; int /*<<< orphan*/  addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  clients; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 TYPE_4__* i2c_new_device (struct i2c_adapter*,struct i2c_board_info*) ; 
 int /*<<< orphan*/  i2c_unregister_device (TYPE_4__*) ; 
 TYPE_3__* keywest_ctx ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct i2c_board_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__* to_i2c_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int keywest_attach_adapter(struct i2c_adapter *adapter)
{
	struct i2c_board_info info;

	if (! keywest_ctx)
		return -EINVAL;

	if (strncmp(adapter->name, "mac-io", 6))
		return -EINVAL; /* ignored */

	memset(&info, 0, sizeof(struct i2c_board_info));
	strlcpy(info.type, "keywest", I2C_NAME_SIZE);
	info.addr = keywest_ctx->addr;
	keywest_ctx->client = i2c_new_device(adapter, &info);
	if (!keywest_ctx->client)
		return -ENODEV;
	/*
	 * We know the driver is already loaded, so the device should be
	 * already bound. If not it means binding failed, and then there
	 * is no point in keeping the device instantiated.
	 */
	if (!keywest_ctx->client->dev.driver) {
		i2c_unregister_device(keywest_ctx->client);
		keywest_ctx->client = NULL;
		return -ENODEV;
	}
	
	/*
	 * Let i2c-core delete that device on driver removal.
	 * This is safe because i2c-core holds the core_lock mutex for us.
	 */
	list_add_tail(&keywest_ctx->client->detected,
		      &to_i2c_driver(keywest_ctx->client->dev.driver)->clients);
	return 0;
}