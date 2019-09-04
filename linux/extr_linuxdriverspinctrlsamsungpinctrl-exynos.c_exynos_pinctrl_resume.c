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
struct samsung_pinctrl_drv_data {int nr_banks; struct samsung_pin_bank* pin_banks; } ;
struct samsung_pin_bank {scalar_t__ eint_type; } ;

/* Variables and functions */
 scalar_t__ EINT_TYPE_GPIO ; 
 int /*<<< orphan*/  exynos_pinctrl_resume_bank (struct samsung_pinctrl_drv_data*,struct samsung_pin_bank*) ; 

void exynos_pinctrl_resume(struct samsung_pinctrl_drv_data *drvdata)
{
	struct samsung_pin_bank *bank = drvdata->pin_banks;
	int i;

	for (i = 0; i < drvdata->nr_banks; ++i, ++bank)
		if (bank->eint_type == EINT_TYPE_GPIO)
			exynos_pinctrl_resume_bank(drvdata, bank);
}