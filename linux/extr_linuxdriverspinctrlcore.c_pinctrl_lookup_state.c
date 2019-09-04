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
struct pinctrl {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct pinctrl_state* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct pinctrl_state* create_state (struct pinctrl*,char const*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char const*) ; 
 struct pinctrl_state* find_state (struct pinctrl*,char const*) ; 
 scalar_t__ pinctrl_dummy_state ; 

struct pinctrl_state *pinctrl_lookup_state(struct pinctrl *p,
						 const char *name)
{
	struct pinctrl_state *state;

	state = find_state(p, name);
	if (!state) {
		if (pinctrl_dummy_state) {
			/* create dummy state */
			dev_dbg(p->dev, "using pinctrl dummy state (%s)\n",
				name);
			state = create_state(p, name);
		} else
			state = ERR_PTR(-ENODEV);
	}

	return state;
}