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
typedef  void* u32 ;
struct wm8903_platform_data {int* gpio_cfg; void* micdet_delay; void* micdet_cfg; } ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int WM8903_GPIO_CONFIG_ZERO ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int,int) ; 
 scalar_t__ of_property_read_u32 (struct device_node const*,char*,void**) ; 
 scalar_t__ of_property_read_u32_array (struct device_node const*,char*,int*,int) ; 

__attribute__((used)) static int wm8903_set_pdata_from_of(struct i2c_client *i2c,
				    struct wm8903_platform_data *pdata)
{
	const struct device_node *np = i2c->dev.of_node;
	u32 val32;
	int i;

	if (of_property_read_u32(np, "micdet-cfg", &val32) >= 0)
		pdata->micdet_cfg = val32;

	if (of_property_read_u32(np, "micdet-delay", &val32) >= 0)
		pdata->micdet_delay = val32;

	if (of_property_read_u32_array(np, "gpio-cfg", pdata->gpio_cfg,
				       ARRAY_SIZE(pdata->gpio_cfg)) >= 0) {
		/*
		 * In device tree: 0 means "write 0",
		 * 0xffffffff means "don't touch".
		 *
		 * In platform data: 0 means "don't touch",
		 * 0x8000 means "write 0".
		 *
		 * Note: WM8903_GPIO_CONFIG_ZERO == 0x8000.
		 *
		 *  Convert from DT to pdata representation here,
		 * so no other code needs to change.
		 */
		for (i = 0; i < ARRAY_SIZE(pdata->gpio_cfg); i++) {
			if (pdata->gpio_cfg[i] == 0) {
				pdata->gpio_cfg[i] = WM8903_GPIO_CONFIG_ZERO;
			} else if (pdata->gpio_cfg[i] == 0xffffffff) {
				pdata->gpio_cfg[i] = 0;
			} else if (pdata->gpio_cfg[i] > 0x7fff) {
				dev_err(&i2c->dev, "Invalid gpio-cfg[%d] %x\n",
					i, pdata->gpio_cfg[i]);
				return -EINVAL;
			}
		}
	}

	return 0;
}