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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pinctrl_unregister (struct pinctrl_dev*) ; 

__attribute__((used)) static void devm_pinctrl_dev_release(struct device *dev, void *res)
{
	struct pinctrl_dev *pctldev = *(struct pinctrl_dev **)res;

	pinctrl_unregister(pctldev);
}