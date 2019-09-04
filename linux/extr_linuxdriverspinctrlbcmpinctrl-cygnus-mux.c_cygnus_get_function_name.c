#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pinctrl_dev {int dummy; } ;
struct cygnus_pinctrl {TYPE_1__* functions; } ;
struct TYPE_2__ {char const* name; } ;

/* Variables and functions */
 struct cygnus_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static const char *cygnus_get_function_name(struct pinctrl_dev *pctrl_dev,
					    unsigned selector)
{
	struct cygnus_pinctrl *pinctrl = pinctrl_dev_get_drvdata(pctrl_dev);

	return pinctrl->functions[selector].name;
}