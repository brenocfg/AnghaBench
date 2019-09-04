#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct exynos_pmu_context {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* pmu_init ) () ;} ;
struct TYPE_5__ {TYPE_3__* pmu_data; struct device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 TYPE_1__* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_of_platform_populate (struct device*) ; 
 TYPE_3__* of_device_get_match_data (struct device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  pmu_base_addr ; 
 TYPE_1__* pmu_context ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static int exynos_pmu_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *res;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	pmu_base_addr = devm_ioremap_resource(dev, res);
	if (IS_ERR(pmu_base_addr))
		return PTR_ERR(pmu_base_addr);

	pmu_context = devm_kzalloc(&pdev->dev,
			sizeof(struct exynos_pmu_context),
			GFP_KERNEL);
	if (!pmu_context)
		return -ENOMEM;
	pmu_context->dev = dev;
	pmu_context->pmu_data = of_device_get_match_data(dev);

	if (pmu_context->pmu_data && pmu_context->pmu_data->pmu_init)
		pmu_context->pmu_data->pmu_init();

	platform_set_drvdata(pdev, pmu_context);

	if (devm_of_platform_populate(dev))
		dev_err(dev, "Error populating children, reboot and poweroff might not work properly\n");

	dev_dbg(dev, "Exynos PMU Driver probe done\n");
	return 0;
}