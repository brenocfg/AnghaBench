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
struct pinctrl_dev {int dummy; } ;
struct madera_pin_private {TYPE_1__* chip; } ;
struct TYPE_4__ {char** group_names; scalar_t__ func; } ;
struct TYPE_3__ {unsigned int n_pins; } ;

/* Variables and functions */
 TYPE_2__* madera_mux_funcs ; 
 struct madera_pin_private* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int madera_mux_get_groups(struct pinctrl_dev *pctldev,
				 unsigned int selector,
				 const char * const **groups,
				 unsigned int * const num_groups)
{
	struct madera_pin_private *priv = pinctrl_dev_get_drvdata(pctldev);

	*groups = madera_mux_funcs[selector].group_names;

	if (madera_mux_funcs[selector].func == 0) {
		/* alt func always maps to a single group */
		*num_groups = 1;
	} else {
		/* other funcs map to all available gpio pins */
		*num_groups = priv->chip->n_pins;
	}

	return 0;
}