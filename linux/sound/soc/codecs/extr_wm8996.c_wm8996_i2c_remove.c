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
struct TYPE_2__ {scalar_t__ ldo_ena; } ;
struct wm8996_priv {TYPE_1__ pdata; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_free (scalar_t__) ; 
 int /*<<< orphan*/  gpio_set_value_cansleep (scalar_t__,int /*<<< orphan*/ ) ; 
 struct wm8996_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  wm8996_free_gpio (struct wm8996_priv*) ; 

__attribute__((used)) static int wm8996_i2c_remove(struct i2c_client *client)
{
	struct wm8996_priv *wm8996 = i2c_get_clientdata(client);

	wm8996_free_gpio(wm8996);
	if (wm8996->pdata.ldo_ena > 0) {
		gpio_set_value_cansleep(wm8996->pdata.ldo_ena, 0);
		gpio_free(wm8996->pdata.ldo_ena);
	}

	return 0;
}