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
struct pinctrl_state {int dummy; } ;
struct pinctrl {struct pinctrl_state* state; } ;

/* Variables and functions */
 int pinctrl_commit_state (struct pinctrl*,struct pinctrl_state*) ; 

int pinctrl_select_state(struct pinctrl *p, struct pinctrl_state *state)
{
	if (p->state == state)
		return 0;

	return pinctrl_commit_state(p, state);
}