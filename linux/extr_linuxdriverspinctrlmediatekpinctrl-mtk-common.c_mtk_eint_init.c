#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_7__ {struct device_node* of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct mtk_pinctrl {TYPE_2__* eint; TYPE_1__* devdata; int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * gpio_xlate; struct mtk_pinctrl* pctl; int /*<<< orphan*/ * hw; int /*<<< orphan*/  regs; TYPE_4__* dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  base; } ;
struct TYPE_5__ {int /*<<< orphan*/  eint_hw; int /*<<< orphan*/  eint_regs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_4__*,struct resource*) ; 
 TYPE_2__* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int mtk_eint_do_init (TYPE_2__*) ; 
 int /*<<< orphan*/  mtk_eint_xt ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_eint_init(struct mtk_pinctrl *pctl, struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct resource *res;

	if (!of_property_read_bool(np, "interrupt-controller"))
		return -ENODEV;

	pctl->eint = devm_kzalloc(pctl->dev, sizeof(*pctl->eint), GFP_KERNEL);
	if (!pctl->eint)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	pctl->eint->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(pctl->eint->base))
		return PTR_ERR(pctl->eint->base);

	pctl->eint->irq = irq_of_parse_and_map(np, 0);
	if (!pctl->eint->irq)
		return -EINVAL;

	pctl->eint->dev = &pdev->dev;
	/*
	 * If pctl->eint->regs == NULL, it would fall back into using a generic
	 * register map in mtk_eint_do_init calls.
	 */
	pctl->eint->regs = pctl->devdata->eint_regs;
	pctl->eint->hw = &pctl->devdata->eint_hw;
	pctl->eint->pctl = pctl;
	pctl->eint->gpio_xlate = &mtk_eint_xt;

	return mtk_eint_do_init(pctl->eint);
}