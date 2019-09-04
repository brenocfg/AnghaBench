#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct ocelot_pinctrl {TYPE_1__* func; } ;
struct device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int ngroups; int /*<<< orphan*/ * groups; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int ENOMEM ; 
 int FUNC_MAX ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ocelot_pin_function_idx (int,int) ; 
 TYPE_2__* ocelot_pins ; 

__attribute__((used)) static int ocelot_create_group_func_map(struct device *dev,
					struct ocelot_pinctrl *info)
{
	u16 pins[ARRAY_SIZE(ocelot_pins)];
	int f, npins, i;

	for (f = 0; f < FUNC_MAX; f++) {
		for (npins = 0, i = 0; i < ARRAY_SIZE(ocelot_pins); i++) {
			if (ocelot_pin_function_idx(i, f) >= 0)
				pins[npins++] = i;
		}

		info->func[f].ngroups = npins;
		info->func[f].groups = devm_kcalloc(dev,
							 npins,
							 sizeof(char *),
							 GFP_KERNEL);
		if (!info->func[f].groups)
			return -ENOMEM;

		for (i = 0; i < npins; i++)
			info->func[f].groups[i] = ocelot_pins[pins[i]].name;
	}

	return 0;
}