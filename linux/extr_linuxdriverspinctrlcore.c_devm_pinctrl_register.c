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
struct pinctrl_dev {int dummy; } ;
struct pinctrl_desc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct pinctrl_dev* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  devm_pinctrl_dev_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct pinctrl_dev**) ; 
 struct pinctrl_dev** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct pinctrl_dev**) ; 
 struct pinctrl_dev* pinctrl_register (struct pinctrl_desc*,struct device*,void*) ; 

struct pinctrl_dev *devm_pinctrl_register(struct device *dev,
					  struct pinctrl_desc *pctldesc,
					  void *driver_data)
{
	struct pinctrl_dev **ptr, *pctldev;

	ptr = devres_alloc(devm_pinctrl_dev_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	pctldev = pinctrl_register(pctldesc, dev, driver_data);
	if (IS_ERR(pctldev)) {
		devres_free(ptr);
		return pctldev;
	}

	*ptr = pctldev;
	devres_add(dev, ptr);

	return pctldev;
}