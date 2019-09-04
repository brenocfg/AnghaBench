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
struct tegra_xusb_padctl {TYPE_1__* soc; } ;
struct pinctrl_dev {int dummy; } ;
struct TYPE_2__ {int num_functions; } ;

/* Variables and functions */
 struct tegra_xusb_padctl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int tegra_xusb_padctl_get_functions_count(struct pinctrl_dev *pinctrl)
{
	struct tegra_xusb_padctl *padctl = pinctrl_dev_get_drvdata(pinctrl);

	return padctl->soc->num_functions;
}