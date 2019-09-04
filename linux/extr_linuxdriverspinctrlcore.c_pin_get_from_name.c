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
struct pinctrl_dev {TYPE_2__* desc; } ;
struct pin_desc {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {unsigned int npins; TYPE_1__* pins; } ;
struct TYPE_3__ {unsigned int number; } ;

/* Variables and functions */
 int EINVAL ; 
 struct pin_desc* pin_desc_get (struct pinctrl_dev*,unsigned int) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

int pin_get_from_name(struct pinctrl_dev *pctldev, const char *name)
{
	unsigned i, pin;

	/* The pin number can be retrived from the pin controller descriptor */
	for (i = 0; i < pctldev->desc->npins; i++) {
		struct pin_desc *desc;

		pin = pctldev->desc->pins[i].number;
		desc = pin_desc_get(pctldev, pin);
		/* Pin space may be sparse */
		if (desc && !strcmp(name, desc->name))
			return pin;
	}

	return -EINVAL;
}