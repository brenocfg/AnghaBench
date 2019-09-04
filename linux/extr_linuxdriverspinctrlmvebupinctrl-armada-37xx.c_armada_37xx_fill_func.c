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
struct armada_37xx_pmx_func {char* name; char** groups; int /*<<< orphan*/  ngroups; } ;
struct armada_37xx_pinctrl {int nfuncs; int ngroups; struct armada_37xx_pin_group* groups; int /*<<< orphan*/  dev; struct armada_37xx_pmx_func* funcs; } ;
struct armada_37xx_pin_group {char* name; int /*<<< orphan*/  funcs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NB_FUNCS ; 
 char** devm_kcalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int match_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int armada_37xx_fill_func(struct armada_37xx_pinctrl *info)
{
	struct armada_37xx_pmx_func *funcs = info->funcs;
	int n;

	for (n = 0; n < info->nfuncs; n++) {
		const char *name = funcs[n].name;
		const char **groups;
		int g;

		funcs[n].groups = devm_kcalloc(info->dev,
					       funcs[n].ngroups,
					       sizeof(*(funcs[n].groups)),
					       GFP_KERNEL);
		if (!funcs[n].groups)
			return -ENOMEM;

		groups = funcs[n].groups;

		for (g = 0; g < info->ngroups; g++) {
			struct armada_37xx_pin_group *gp = &info->groups[g];
			int f;

			f = match_string(gp->funcs, NB_FUNCS, name);
			if (f < 0)
				continue;

			*groups = gp->name;
			groups++;
		}
	}
	return 0;
}