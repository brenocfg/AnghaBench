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
struct pinctrl {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct pinctrl* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct pinctrl*) ; 
 int /*<<< orphan*/  devm_pinctrl_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct pinctrl**) ; 
 struct pinctrl** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct pinctrl**) ; 
 struct pinctrl* pinctrl_get (struct device*) ; 

struct pinctrl *devm_pinctrl_get(struct device *dev)
{
	struct pinctrl **ptr, *p;

	ptr = devres_alloc(devm_pinctrl_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	p = pinctrl_get(dev);
	if (!IS_ERR(p)) {
		*ptr = p;
		devres_add(dev, ptr);
	} else {
		devres_free(ptr);
	}

	return p;
}