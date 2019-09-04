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
struct pinctrl_gpio_range {int /*<<< orphan*/  node; } ;
struct pinctrl_dev {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void pinctrl_remove_gpio_range(struct pinctrl_dev *pctldev,
			       struct pinctrl_gpio_range *range)
{
	mutex_lock(&pctldev->mutex);
	list_del(&range->node);
	mutex_unlock(&pctldev->mutex);
}