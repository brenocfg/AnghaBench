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
struct gab_platform_data {int gpio_inverted; int /*<<< orphan*/  gpio_charge_finished; } ;
struct gab {struct gab_platform_data* pdata; } ;

/* Variables and functions */
 int gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_is_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool gab_charge_finished(struct gab *adc_bat)
{
	struct gab_platform_data *pdata = adc_bat->pdata;
	bool ret = gpio_get_value(pdata->gpio_charge_finished);
	bool inv = pdata->gpio_inverted;

	if (!gpio_is_valid(pdata->gpio_charge_finished))
		return false;
	return ret ^ inv;
}