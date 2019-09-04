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
typedef  int /*<<< orphan*/  u32 ;
struct device_node {int dummy; } ;
struct at91_pinctrl {int nmux; int /*<<< orphan*/  dev; int /*<<< orphan*/  mux_mask; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int gpio_banks ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int*) ; 
 int of_property_read_u32_array (struct device_node*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int at91_pinctrl_mux_mask(struct at91_pinctrl *info,
				 struct device_node *np)
{
	int ret = 0;
	int size;
	const __be32 *list;

	list = of_get_property(np, "atmel,mux-mask", &size);
	if (!list) {
		dev_err(info->dev, "can not read the mux-mask of %d\n", size);
		return -EINVAL;
	}

	size /= sizeof(*list);
	if (!size || size % gpio_banks) {
		dev_err(info->dev, "wrong mux mask array should be by %d\n", gpio_banks);
		return -EINVAL;
	}
	info->nmux = size / gpio_banks;

	info->mux_mask = devm_kcalloc(info->dev, size, sizeof(u32),
				      GFP_KERNEL);
	if (!info->mux_mask)
		return -ENOMEM;

	ret = of_property_read_u32_array(np, "atmel,mux-mask",
					  info->mux_mask, size);
	if (ret)
		dev_err(info->dev, "can not read the mux-mask of %d\n", size);
	return ret;
}