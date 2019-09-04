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
struct wl1251 {int /*<<< orphan*/  power_gpio; } ;
struct sdio_func {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_disable_func (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_enable_func (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 struct sdio_func* wl_to_func (struct wl1251*) ; 

__attribute__((used)) static int wl1251_sdio_set_power(struct wl1251 *wl, bool enable)
{
	struct sdio_func *func = wl_to_func(wl);
	int ret;

	if (enable) {
		/*
		 * Power is controlled by runtime PM, but we still call board
		 * callback in case it wants to do any additional setup,
		 * for example enabling clock buffer for the module.
		 */
		if (gpio_is_valid(wl->power_gpio))
			gpio_set_value(wl->power_gpio, true);


		ret = pm_runtime_get_sync(&func->dev);
		if (ret < 0) {
			pm_runtime_put_sync(&func->dev);
			goto out;
		}

		sdio_claim_host(func);
		sdio_enable_func(func);
		sdio_release_host(func);
	} else {
		sdio_claim_host(func);
		sdio_disable_func(func);
		sdio_release_host(func);

		ret = pm_runtime_put_sync(&func->dev);
		if (ret < 0)
			goto out;

		if (gpio_is_valid(wl->power_gpio))
			gpio_set_value(wl->power_gpio, false);
	}

out:
	return ret;
}