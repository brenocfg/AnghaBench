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
struct hist_trigger_attrs {size_t n_actions; int /*<<< orphan*/ * action_str; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t HIST_ACTIONS_MAX ; 
 int /*<<< orphan*/  kstrdup (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ str_has_prefix (char*,char*) ; 

__attribute__((used)) static int parse_action(char *str, struct hist_trigger_attrs *attrs)
{
	int ret = -EINVAL;

	if (attrs->n_actions >= HIST_ACTIONS_MAX)
		return ret;

	if ((str_has_prefix(str, "onmatch(")) ||
	    (str_has_prefix(str, "onmax(")) ||
	    (str_has_prefix(str, "onchange("))) {
		attrs->action_str[attrs->n_actions] = kstrdup(str, GFP_KERNEL);
		if (!attrs->action_str[attrs->n_actions]) {
			ret = -ENOMEM;
			return ret;
		}
		attrs->n_actions++;
		ret = 0;
	}
	return ret;
}