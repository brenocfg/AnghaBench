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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct cs35l34_private {int /*<<< orphan*/  core_supplies; int /*<<< orphan*/  num_core_supplies; int /*<<< orphan*/  reset_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cs35l34_private* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs35l34_i2c_remove(struct i2c_client *client)
{
	struct cs35l34_private *cs35l34 = i2c_get_clientdata(client);

	gpiod_set_value_cansleep(cs35l34->reset_gpio, 0);

	pm_runtime_disable(&client->dev);
	regulator_bulk_disable(cs35l34->num_core_supplies,
		cs35l34->core_supplies);

	return 0;
}