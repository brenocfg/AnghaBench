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
struct TYPE_4__ {unsigned int* pins; unsigned int n_pins; } ;
struct TYPE_3__ {unsigned int n_pin_groups; TYPE_2__* pin_groups; } ;

/* Variables and functions */
 unsigned int* madera_pin_single_group_pins ; 
 struct madera_pin_private* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int madera_get_group_pins(struct pinctrl_dev *pctldev,
				 unsigned int selector,
				 const unsigned int **pins,
				 unsigned int *num_pins)
{
	struct madera_pin_private *priv = pinctrl_dev_get_drvdata(pctldev);

	if (selector < priv->chip->n_pin_groups) {
		*pins = priv->chip->pin_groups[selector].pins;
		*num_pins = priv->chip->pin_groups[selector].n_pins;
	} else {
		/* return the dummy group for a single pin */
		selector -= priv->chip->n_pin_groups;
		*pins = &madera_pin_single_group_pins[selector];
		*num_pins = 1;
	}
	return 0;
}