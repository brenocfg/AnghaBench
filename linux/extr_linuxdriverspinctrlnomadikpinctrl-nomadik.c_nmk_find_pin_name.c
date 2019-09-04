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
struct nmk_pinctrl {TYPE_1__* soc; } ;
struct TYPE_4__ {int number; char const* name; } ;
struct TYPE_3__ {int npins; TYPE_2__* pins; } ;

/* Variables and functions */
 struct nmk_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int sscanf (char*,char*,int*) ; 

__attribute__((used)) static const char *nmk_find_pin_name(struct pinctrl_dev *pctldev, const char *pin_name)
{
	int i, pin_number;
	struct nmk_pinctrl *npct = pinctrl_dev_get_drvdata(pctldev);

	if (sscanf((char *)pin_name, "GPIO%d", &pin_number) == 1)
		for (i = 0; i < npct->soc->npins; i++)
			if (npct->soc->pins[i].number == pin_number)
				return npct->soc->pins[i].name;
	return NULL;
}