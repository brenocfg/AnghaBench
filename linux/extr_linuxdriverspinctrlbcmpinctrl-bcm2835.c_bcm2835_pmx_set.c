#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pinctrl_dev {int dummy; } ;
struct bcm2835_pinctrl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm2835_pinctrl_fsel_set (struct bcm2835_pinctrl*,unsigned int,unsigned int) ; 
 struct bcm2835_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int bcm2835_pmx_set(struct pinctrl_dev *pctldev,
		unsigned func_selector,
		unsigned group_selector)
{
	struct bcm2835_pinctrl *pc = pinctrl_dev_get_drvdata(pctldev);

	bcm2835_pinctrl_fsel_set(pc, group_selector, func_selector);

	return 0;
}