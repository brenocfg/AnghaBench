#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct zynq_pinctrl {int /*<<< orphan*/  pctrl; void* nfuncs; void* funcs; void* ngroups; void* groups; int /*<<< orphan*/  pctrl_offset; int /*<<< orphan*/  syscon; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 struct zynq_pinctrl* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pinctrl_register (TYPE_1__*,int /*<<< orphan*/ *,struct zynq_pinctrl*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct zynq_pinctrl*) ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zynq_desc ; 
 void* zynq_pctrl_groups ; 
 void* zynq_pmux_functions ; 

__attribute__((used)) static int zynq_pinctrl_probe(struct platform_device *pdev)

{
	struct resource *res;
	struct zynq_pinctrl *pctrl;

	pctrl = devm_kzalloc(&pdev->dev, sizeof(*pctrl), GFP_KERNEL);
	if (!pctrl)
		return -ENOMEM;

	pctrl->syscon = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
							"syscon");
	if (IS_ERR(pctrl->syscon)) {
		dev_err(&pdev->dev, "unable to get syscon\n");
		return PTR_ERR(pctrl->syscon);
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "missing IO resource\n");
		return -ENODEV;
	}
	pctrl->pctrl_offset = res->start;

	pctrl->groups = zynq_pctrl_groups;
	pctrl->ngroups = ARRAY_SIZE(zynq_pctrl_groups);
	pctrl->funcs = zynq_pmux_functions;
	pctrl->nfuncs = ARRAY_SIZE(zynq_pmux_functions);

	pctrl->pctrl = devm_pinctrl_register(&pdev->dev, &zynq_desc, pctrl);
	if (IS_ERR(pctrl->pctrl))
		return PTR_ERR(pctrl->pctrl);

	platform_set_drvdata(pdev, pctrl);

	dev_info(&pdev->dev, "zynq pinctrl initialized\n");

	return 0;
}