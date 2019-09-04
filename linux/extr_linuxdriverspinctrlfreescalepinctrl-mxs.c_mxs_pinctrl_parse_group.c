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
typedef  int u32 ;
struct property {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mxs_pinctrl_data {TYPE_1__* soc; } ;
struct mxs_group {char* name; int npins; int /*<<< orphan*/ * pins; int /*<<< orphan*/ * muxsel; } ;
struct device_node {char* name; } ;
struct TYPE_2__ {struct mxs_group* groups; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MUXID_TO_MUXSEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUXID_TO_PINID (int /*<<< orphan*/ ) ; 
 int SUFFIX_LEN ; 
 void* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 char* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct property* of_find_property (struct device_node*,char const*,int*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  of_property_read_u32_array (struct device_node*,char const*,int /*<<< orphan*/ *,int) ; 
 struct mxs_pinctrl_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int strlen (char*) ; 

__attribute__((used)) static int mxs_pinctrl_parse_group(struct platform_device *pdev,
				   struct device_node *np, int idx,
				   const char **out_name)
{
	struct mxs_pinctrl_data *d = platform_get_drvdata(pdev);
	struct mxs_group *g = &d->soc->groups[idx];
	struct property *prop;
	const char *propname = "fsl,pinmux-ids";
	char *group;
	int length = strlen(np->name) + SUFFIX_LEN;
	u32 val, i;

	group = devm_kzalloc(&pdev->dev, length, GFP_KERNEL);
	if (!group)
		return -ENOMEM;
	if (of_property_read_u32(np, "reg", &val))
		snprintf(group, length, "%s", np->name);
	else
		snprintf(group, length, "%s.%d", np->name, val);
	g->name = group;

	prop = of_find_property(np, propname, &length);
	if (!prop)
		return -EINVAL;
	g->npins = length / sizeof(u32);

	g->pins = devm_kcalloc(&pdev->dev, g->npins, sizeof(*g->pins),
			       GFP_KERNEL);
	if (!g->pins)
		return -ENOMEM;

	g->muxsel = devm_kcalloc(&pdev->dev, g->npins, sizeof(*g->muxsel),
				 GFP_KERNEL);
	if (!g->muxsel)
		return -ENOMEM;

	of_property_read_u32_array(np, propname, g->pins, g->npins);
	for (i = 0; i < g->npins; i++) {
		g->muxsel[i] = MUXID_TO_MUXSEL(g->pins[i]);
		g->pins[i] = MUXID_TO_PINID(g->pins[i]);
	}

	if (out_name)
		*out_name = g->name;

	return 0;
}