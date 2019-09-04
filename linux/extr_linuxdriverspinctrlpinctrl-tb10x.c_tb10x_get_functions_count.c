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
struct tb10x_pinctrl {int pinfuncnt; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 struct tb10x_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int tb10x_get_functions_count(struct pinctrl_dev *pctl)
{
	struct tb10x_pinctrl *state = pinctrl_dev_get_drvdata(pctl);
	return state->pinfuncnt;
}