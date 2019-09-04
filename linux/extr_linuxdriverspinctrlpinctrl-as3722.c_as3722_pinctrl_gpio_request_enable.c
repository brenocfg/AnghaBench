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
struct pinctrl_gpio_range {int dummy; } ;
struct pinctrl_dev {int dummy; } ;
struct as3722_pctrl_info {TYPE_1__* gpio_control; } ;
struct TYPE_2__ {scalar_t__ io_function; } ;

/* Variables and functions */
 int EBUSY ; 
 struct as3722_pctrl_info* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int as3722_pinctrl_gpio_request_enable(struct pinctrl_dev *pctldev,
		struct pinctrl_gpio_range *range, unsigned offset)
{
	struct as3722_pctrl_info *as_pci = pinctrl_dev_get_drvdata(pctldev);

	if (as_pci->gpio_control[offset].io_function)
		return -EBUSY;
	return 0;
}