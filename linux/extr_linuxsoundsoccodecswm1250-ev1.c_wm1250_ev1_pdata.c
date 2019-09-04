#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wm1250_priv {TYPE_1__* gpios; } ;
struct wm1250_ev1_pdata {int /*<<< orphan*/ * gpios; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {void* flags; int /*<<< orphan*/  label; int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* GPIOF_OUT_INIT_HIGH ; 
 void* GPIOF_OUT_INIT_LOW ; 
 size_t WM1250_EV1_GPIO_CLK_SEL0 ; 
 size_t WM1250_EV1_GPIO_CLK_SEL1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct wm1250_ev1_pdata* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct wm1250_priv*) ; 
 struct wm1250_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int gpio_request_array (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * wm1250_gpio_names ; 

__attribute__((used)) static int wm1250_ev1_pdata(struct i2c_client *i2c)
{
	struct wm1250_ev1_pdata *pdata = dev_get_platdata(&i2c->dev);
	struct wm1250_priv *wm1250;
	int i, ret;

	if (!pdata)
		return 0;

	wm1250 = devm_kzalloc(&i2c->dev, sizeof(*wm1250), GFP_KERNEL);
	if (!wm1250) {
		ret = -ENOMEM;
		goto err;
	}

	for (i = 0; i < ARRAY_SIZE(wm1250->gpios); i++) {
		wm1250->gpios[i].gpio = pdata->gpios[i];
		wm1250->gpios[i].label = wm1250_gpio_names[i];
		wm1250->gpios[i].flags = GPIOF_OUT_INIT_LOW;
	}
	wm1250->gpios[WM1250_EV1_GPIO_CLK_SEL0].flags = GPIOF_OUT_INIT_HIGH;
	wm1250->gpios[WM1250_EV1_GPIO_CLK_SEL1].flags = GPIOF_OUT_INIT_HIGH;

	ret = gpio_request_array(wm1250->gpios, ARRAY_SIZE(wm1250->gpios));
	if (ret != 0) {
		dev_err(&i2c->dev, "Failed to get GPIOs: %d\n", ret);
		goto err;
	}

	dev_set_drvdata(&i2c->dev, wm1250);

	return ret;

err:
	return ret;
}