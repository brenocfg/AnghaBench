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
struct sunxi_pinctrl {int variant; TYPE_2__* desc; } ;
struct TYPE_3__ {scalar_t__ name; } ;
struct sunxi_desc_pin {struct sunxi_desc_function* functions; TYPE_1__ pin; } ;
struct sunxi_desc_function {int variant; scalar_t__ name; } ;
struct TYPE_4__ {int npins; struct sunxi_desc_pin* pins; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static struct sunxi_desc_function *
sunxi_pinctrl_desc_find_function_by_name(struct sunxi_pinctrl *pctl,
					 const char *pin_name,
					 const char *func_name)
{
	int i;

	for (i = 0; i < pctl->desc->npins; i++) {
		const struct sunxi_desc_pin *pin = pctl->desc->pins + i;

		if (!strcmp(pin->pin.name, pin_name)) {
			struct sunxi_desc_function *func = pin->functions;

			while (func->name) {
				if (!strcmp(func->name, func_name) &&
					(!func->variant ||
					func->variant & pctl->variant))
					return func;

				func++;
			}
		}
	}

	return NULL;
}