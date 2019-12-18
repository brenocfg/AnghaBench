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
struct aic3x_priv {int /*<<< orphan*/  gpio_reset; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  aic3x_is_shared_reset (struct aic3x_priv*) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aic3x_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aic3x_i2c_remove(struct i2c_client *client)
{
	struct aic3x_priv *aic3x = i2c_get_clientdata(client);

	list_del(&aic3x->list);

	if (gpio_is_valid(aic3x->gpio_reset) &&
	    !aic3x_is_shared_reset(aic3x)) {
		gpio_set_value(aic3x->gpio_reset, 0);
		gpio_free(aic3x->gpio_reset);
	}
	return 0;
}