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
struct spear_pmx {TYPE_1__* machdata; } ;
struct spear_gpio_pingroup {int npins; unsigned int* pins; } ;
struct TYPE_2__ {int ngpio_pingroups; struct spear_gpio_pingroup* gpio_pingroups; } ;

/* Variables and functions */

__attribute__((used)) static struct spear_gpio_pingroup *get_gpio_pingroup(struct spear_pmx *pmx,
		unsigned pin)
{
	struct spear_gpio_pingroup *gpio_pingroup;
	int i, j;

	if (!pmx->machdata->gpio_pingroups)
		return NULL;

	for (i = 0; i < pmx->machdata->ngpio_pingroups; i++) {
		gpio_pingroup = &pmx->machdata->gpio_pingroups[i];

		for (j = 0; j < gpio_pingroup->npins; j++) {
			if (gpio_pingroup->pins[j] == pin)
				return gpio_pingroup;
		}
	}

	return NULL;
}