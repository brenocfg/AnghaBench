#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tas571x_private {int /*<<< orphan*/  supplies; TYPE_1__* chip; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_supply_names; } ;

/* Variables and functions */
 struct tas571x_private* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tas571x_i2c_remove(struct i2c_client *client)
{
	struct tas571x_private *priv = i2c_get_clientdata(client);

	regulator_bulk_disable(priv->chip->num_supply_names, priv->supplies);

	return 0;
}