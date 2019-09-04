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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct artpec6_pmx {int /*<<< orphan*/  pctl; void* num_pin_groups; void* pin_groups; void* num_functions; void* functions; void* num_pins; void* pins; int /*<<< orphan*/  base; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  artpec6_desc ; 
 void* artpec6_pin_groups ; 
 void* artpec6_pins ; 
 void* artpec6_pmx_functions ; 
 int /*<<< orphan*/  artpec6_pmx_reset (struct artpec6_pmx*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct artpec6_pmx* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinctrl_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct artpec6_pmx*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct artpec6_pmx*) ; 

__attribute__((used)) static int artpec6_pmx_probe(struct platform_device *pdev)
{
	struct artpec6_pmx *pmx;
	struct resource *res;

	pmx = devm_kzalloc(&pdev->dev, sizeof(*pmx), GFP_KERNEL);
	if (!pmx)
		return -ENOMEM;

	pmx->dev = &pdev->dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	pmx->base = devm_ioremap_resource(&pdev->dev, res);

	if (IS_ERR(pmx->base))
		return PTR_ERR(pmx->base);

	artpec6_pmx_reset(pmx);

	pmx->pins	    = artpec6_pins;
	pmx->num_pins	    = ARRAY_SIZE(artpec6_pins);
	pmx->functions	    = artpec6_pmx_functions;
	pmx->num_functions  = ARRAY_SIZE(artpec6_pmx_functions);
	pmx->pin_groups	    = artpec6_pin_groups;
	pmx->num_pin_groups = ARRAY_SIZE(artpec6_pin_groups);
	pmx->pctl	    = pinctrl_register(&artpec6_desc, &pdev->dev, pmx);

	if (IS_ERR(pmx->pctl)) {
		dev_err(&pdev->dev, "could not register pinctrl driver\n");
		return PTR_ERR(pmx->pctl);
	}

	platform_set_drvdata(pdev, pmx);

	dev_info(&pdev->dev, "initialised Axis ARTPEC-6 pinctrl driver\n");

	return 0;
}