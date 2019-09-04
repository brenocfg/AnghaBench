#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct stm32_pinctrl {TYPE_1__* match_data; } ;
struct TYPE_4__ {scalar_t__ number; } ;
struct stm32_desc_pin {TYPE_2__ pin; struct stm32_desc_function* functions; } ;
struct stm32_desc_function {scalar_t__ num; scalar_t__ name; } ;
struct TYPE_3__ {int npins; struct stm32_desc_pin* pins; } ;

/* Variables and functions */

__attribute__((used)) static bool stm32_pctrl_is_function_valid(struct stm32_pinctrl *pctl,
		u32 pin_num, u32 fnum)
{
	int i;

	for (i = 0; i < pctl->match_data->npins; i++) {
		const struct stm32_desc_pin *pin = pctl->match_data->pins + i;
		const struct stm32_desc_function *func = pin->functions;

		if (pin->pin.number != pin_num)
			continue;

		while (func && func->name) {
			if (func->num == fnum)
				return true;
			func++;
		}

		break;
	}

	return false;
}