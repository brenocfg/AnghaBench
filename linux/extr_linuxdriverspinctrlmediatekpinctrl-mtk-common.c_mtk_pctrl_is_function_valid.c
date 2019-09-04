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
struct mtk_pinctrl {TYPE_1__* devdata; } ;
struct TYPE_4__ {scalar_t__ number; } ;
struct mtk_desc_pin {struct mtk_desc_function* functions; TYPE_2__ pin; } ;
struct mtk_desc_function {scalar_t__ muxval; scalar_t__ name; } ;
struct TYPE_3__ {int npins; struct mtk_desc_pin* pins; } ;

/* Variables and functions */

__attribute__((used)) static bool mtk_pctrl_is_function_valid(struct mtk_pinctrl *pctl,
		u32 pin_num, u32 fnum)
{
	int i;

	for (i = 0; i < pctl->devdata->npins; i++) {
		const struct mtk_desc_pin *pin = pctl->devdata->pins + i;

		if (pin->pin.number == pin_num) {
			const struct mtk_desc_function *func =
					pin->functions;

			while (func && func->name) {
				if (func->muxval == fnum)
					return true;
				func++;
			}

			break;
		}
	}

	return false;
}