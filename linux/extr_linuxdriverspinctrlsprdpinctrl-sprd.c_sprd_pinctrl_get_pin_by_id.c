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
struct sprd_pinctrl_soc_info {int npins; struct sprd_pin* pins; } ;
struct sprd_pinctrl {struct sprd_pinctrl_soc_info* info; } ;
struct sprd_pin {unsigned int number; } ;

/* Variables and functions */

__attribute__((used)) static struct sprd_pin *
sprd_pinctrl_get_pin_by_id(struct sprd_pinctrl *sprd_pctl, unsigned int id)
{
	struct sprd_pinctrl_soc_info *info = sprd_pctl->info;
	struct sprd_pin *pin = NULL;
	int i;

	for (i = 0; i < info->npins; i++) {
		if (info->pins[i].number == id) {
			pin = &info->pins[i];
			break;
		}
	}

	return pin;
}