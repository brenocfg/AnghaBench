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
struct zx_pinctrl_soc_info {int npins; struct pinctrl_pin_desc* pins; } ;
struct zx_pinctrl {struct pinctrl_dev* pctldev; struct zx_pinctrl_soc_info* info; } ;
struct zx_pin_data {struct zx_mux_desc* muxes; } ;
struct zx_mux_desc {char* name; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct pinctrl_pin_desc {char* name; struct zx_pin_data* drv_data; int /*<<< orphan*/  number; } ;
struct pinctrl_dev {int num_groups; int num_functions; int /*<<< orphan*/  pin_function_tree; int /*<<< orphan*/  pin_group_tree; } ;
struct group_desc {char* name; int* pins; int num_pins; int num_group_names; char** group_names; } ;
struct function_desc {char* name; int* pins; int num_pins; int num_group_names; char** group_names; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 struct group_desc* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct group_desc*) ; 
 struct group_desc* krealloc (struct group_desc*,int,int /*<<< orphan*/ ) ; 
 struct zx_pinctrl* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  radix_tree_insert (int /*<<< orphan*/ *,int,struct group_desc*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int zx_pinctrl_build_state(struct platform_device *pdev)
{
	struct zx_pinctrl *zpctl = platform_get_drvdata(pdev);
	struct zx_pinctrl_soc_info *info = zpctl->info;
	struct pinctrl_dev *pctldev = zpctl->pctldev;
	struct function_desc *functions;
	int nfunctions;
	struct group_desc *groups;
	int ngroups;
	int i;

	/* Every single pin composes a group */
	ngroups = info->npins;
	groups = devm_kcalloc(&pdev->dev, ngroups, sizeof(*groups),
			      GFP_KERNEL);
	if (!groups)
		return -ENOMEM;

	for (i = 0; i < ngroups; i++) {
		const struct pinctrl_pin_desc *pindesc = info->pins + i;
		struct group_desc *group = groups + i;

		group->name = pindesc->name;
		group->pins = (int *) &pindesc->number;
		group->num_pins = 1;
		radix_tree_insert(&pctldev->pin_group_tree, i, group);
	}

	pctldev->num_groups = ngroups;

	/* Build function list from pin mux functions */
	functions = kcalloc(info->npins, sizeof(*functions), GFP_KERNEL);
	if (!functions)
		return -ENOMEM;

	nfunctions = 0;
	for (i = 0; i < info->npins; i++) {
		const struct pinctrl_pin_desc *pindesc = info->pins + i;
		struct zx_pin_data *data = pindesc->drv_data;
		struct zx_mux_desc *mux;

		/* Reserved pins do not have a drv_data at all */
		if (!data)
			continue;

		/* Loop over all muxes for the pin */
		mux = data->muxes;
		while (mux->name) {
			struct function_desc *func = functions;

			/* Search function list for given mux */
			while (func->name) {
				if (strcmp(mux->name, func->name) == 0) {
					/* Function exists */
					func->num_group_names++;
					break;
				}
				func++;
			}

			if (!func->name) {
				/* New function */
				func->name = mux->name;
				func->num_group_names = 1;
				radix_tree_insert(&pctldev->pin_function_tree,
						  nfunctions++, func);
			}

			mux++;
		}
	}

	pctldev->num_functions = nfunctions;
	functions = krealloc(functions, nfunctions * sizeof(*functions),
			     GFP_KERNEL);

	/* Find pin groups for every single function */
	for (i = 0; i < info->npins; i++) {
		const struct pinctrl_pin_desc *pindesc = info->pins + i;
		struct zx_pin_data *data = pindesc->drv_data;
		struct zx_mux_desc *mux;

		if (!data)
			continue;

		mux = data->muxes;
		while (mux->name) {
			struct function_desc *func;
			const char **group;
			int j;

			/* Find function for given mux */
			for (j = 0; j < nfunctions; j++)
				if (strcmp(functions[j].name, mux->name) == 0)
					break;

			func = functions + j;
			if (!func->group_names) {
				func->group_names = devm_kcalloc(&pdev->dev,
						func->num_group_names,
						sizeof(*func->group_names),
						GFP_KERNEL);
				if (!func->group_names) {
					kfree(functions);
					return -ENOMEM;
				}
			}

			group = func->group_names;
			while (*group)
				group++;
			*group = pindesc->name;

			mux++;
		}
	}

	return 0;
}