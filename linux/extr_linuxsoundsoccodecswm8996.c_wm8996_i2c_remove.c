#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ ldo_ena; } ;
struct wm8996_priv {int /*<<< orphan*/ * disable_nb; TYPE_2__* supplies; TYPE_1__ pdata; } ;
struct i2c_client {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  gpio_free (scalar_t__) ; 
 int /*<<< orphan*/  gpio_set_value_cansleep (scalar_t__,int /*<<< orphan*/ ) ; 
 struct wm8996_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  regulator_unregister_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wm8996_free_gpio (struct wm8996_priv*) ; 

__attribute__((used)) static int wm8996_i2c_remove(struct i2c_client *client)
{
	struct wm8996_priv *wm8996 = i2c_get_clientdata(client);
	int i;

	wm8996_free_gpio(wm8996);
	if (wm8996->pdata.ldo_ena > 0) {
		gpio_set_value_cansleep(wm8996->pdata.ldo_ena, 0);
		gpio_free(wm8996->pdata.ldo_ena);
	}
	for (i = 0; i < ARRAY_SIZE(wm8996->supplies); i++)
		regulator_unregister_notifier(wm8996->supplies[i].consumer,
					      &wm8996->disable_nb[i]);

	return 0;
}