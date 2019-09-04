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
struct u300_pmx {int /*<<< orphan*/  pctl; int /*<<< orphan*/  virtbase; int /*<<< orphan*/ * dev; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct u300_pmx* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pinctrl_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct u300_pmx*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct u300_pmx*) ; 
 int /*<<< orphan*/  u300_pmx_desc ; 

__attribute__((used)) static int u300_pmx_probe(struct platform_device *pdev)
{
	struct u300_pmx *upmx;
	struct resource *res;

	/* Create state holders etc for this driver */
	upmx = devm_kzalloc(&pdev->dev, sizeof(*upmx), GFP_KERNEL);
	if (!upmx)
		return -ENOMEM;

	upmx->dev = &pdev->dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	upmx->virtbase = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(upmx->virtbase))
		return PTR_ERR(upmx->virtbase);

	upmx->pctl = devm_pinctrl_register(&pdev->dev, &u300_pmx_desc, upmx);
	if (IS_ERR(upmx->pctl)) {
		dev_err(&pdev->dev, "could not register U300 pinmux driver\n");
		return PTR_ERR(upmx->pctl);
	}

	platform_set_drvdata(pdev, upmx);

	dev_info(&pdev->dev, "initialized U300 pin control driver\n");

	return 0;
}