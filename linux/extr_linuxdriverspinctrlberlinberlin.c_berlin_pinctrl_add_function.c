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
struct berlin_pinctrl_function {char const* name; int ngroups; } ;
struct berlin_pinctrl {int /*<<< orphan*/  nfunctions; struct berlin_pinctrl_function* functions; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

__attribute__((used)) static int berlin_pinctrl_add_function(struct berlin_pinctrl *pctrl,
				       const char *name)
{
	struct berlin_pinctrl_function *function = pctrl->functions;

	while (function->name) {
		if (!strcmp(function->name, name)) {
			function->ngroups++;
			return -EEXIST;
		}
		function++;
	}

	function->name = name;
	function->ngroups = 1;

	pctrl->nfunctions++;

	return 0;
}