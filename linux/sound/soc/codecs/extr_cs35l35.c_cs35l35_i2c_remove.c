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
struct i2c_client {int dummy; } ;
struct cs35l35_private {int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  supplies; int /*<<< orphan*/  num_supplies; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cs35l35_private* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs35l35_i2c_remove(struct i2c_client *i2c_client)
{
	struct cs35l35_private *cs35l35 = i2c_get_clientdata(i2c_client);

	regulator_bulk_disable(cs35l35->num_supplies, cs35l35->supplies);
	gpiod_set_value_cansleep(cs35l35->reset_gpio, 0);

	return 0;
}