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
struct TYPE_2__ {scalar_t__ hp_pol; } ;
struct wm5100_priv {TYPE_1__ pdata; struct snd_soc_component* component; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct i2c_client {int /*<<< orphan*/  dev; scalar_t__ irq; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_HIGH ; 
 int /*<<< orphan*/  WM5100_IRQ_DEBOUNCE_1 ; 
 int /*<<< orphan*/  WM5100_IRQ_DEBOUNCE_2 ; 
 int /*<<< orphan*/  WM5100_OUT_VU ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__,int) ; 
 int gpio_request_one (scalar_t__,int /*<<< orphan*/ ,char*) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct wm5100_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_new_controls (struct snd_soc_dapm_context*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wm5100_dapm_widgets_noirq ; 
 int /*<<< orphan*/ * wm5100_dig_vu ; 

__attribute__((used)) static int wm5100_probe(struct snd_soc_component *component)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct i2c_client *i2c = to_i2c_client(component->dev);
	struct wm5100_priv *wm5100 = snd_soc_component_get_drvdata(component);
	int ret, i;

	wm5100->component = component;

	for (i = 0; i < ARRAY_SIZE(wm5100_dig_vu); i++)
		snd_soc_component_update_bits(component, wm5100_dig_vu[i], WM5100_OUT_VU,
				    WM5100_OUT_VU);

	/* Don't debounce interrupts to support use of SYSCLK only */
	snd_soc_component_write(component, WM5100_IRQ_DEBOUNCE_1, 0);
	snd_soc_component_write(component, WM5100_IRQ_DEBOUNCE_2, 0);

	/* TODO: check if we're symmetric */

	if (i2c->irq)
		snd_soc_dapm_new_controls(dapm, wm5100_dapm_widgets_noirq,
					  ARRAY_SIZE(wm5100_dapm_widgets_noirq));

	if (wm5100->pdata.hp_pol) {
		ret = gpio_request_one(wm5100->pdata.hp_pol,
				       GPIOF_OUT_INIT_HIGH, "WM5100 HP_POL");
		if (ret < 0) {
			dev_err(&i2c->dev, "Failed to request HP_POL %d: %d\n",
				wm5100->pdata.hp_pol, ret);
			goto err_gpio;
		}
	}

	return 0;

err_gpio:

	return ret;
}