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
struct TYPE_4__ {TYPE_1__* pins; } ;
struct pm8xxx_mpp {TYPE_2__ desc; } ;
struct pinctrl_dev {int dummy; } ;
struct TYPE_3__ {unsigned int number; } ;

/* Variables and functions */
 struct pm8xxx_mpp* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int pm8xxx_get_group_pins(struct pinctrl_dev *pctldev,
				 unsigned group,
				 const unsigned **pins,
				 unsigned *num_pins)
{
	struct pm8xxx_mpp *pctrl = pinctrl_dev_get_drvdata(pctldev);

	*pins = &pctrl->desc.pins[group].number;
	*num_pins = 1;

	return 0;
}