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
struct resource {unsigned int start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct arm_ccn {unsigned int irq; void* xp; void* node; int /*<<< orphan*/  num_xps; int /*<<< orphan*/ * dev; int /*<<< orphan*/  num_nodes; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ CCN_MN_ERRINT_STATUS ; 
 int /*<<< orphan*/  CCN_MN_ERRINT_STATUS__PMU_EVENTS__DISABLE ; 
 int CCN_MN_ERRINT_STATUS__PMU_EVENTS__DISABLED ; 
 int /*<<< orphan*/  CCN_MN_ERRINT_STATUS__PMU_EVENTS__ENABLE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int IRQF_NOBALANCING ; 
 int IRQF_NO_THREAD ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int arm_ccn_for_each_valid_region (struct arm_ccn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_ccn_get_nodes_num ; 
 int /*<<< orphan*/  arm_ccn_init_nodes ; 
 int /*<<< orphan*/  arm_ccn_irq_handler ; 
 int arm_ccn_pmu_init (struct arm_ccn*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 scalar_t__ devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 void* devm_kcalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct arm_ccn* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct arm_ccn*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct arm_ccn*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int arm_ccn_probe(struct platform_device *pdev)
{
	struct arm_ccn *ccn;
	struct resource *res;
	unsigned int irq;
	int err;

	ccn = devm_kzalloc(&pdev->dev, sizeof(*ccn), GFP_KERNEL);
	if (!ccn)
		return -ENOMEM;
	ccn->dev = &pdev->dev;
	platform_set_drvdata(pdev, ccn);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	ccn->base = devm_ioremap_resource(ccn->dev, res);
	if (IS_ERR(ccn->base))
		return PTR_ERR(ccn->base);

	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!res)
		return -EINVAL;
	irq = res->start;

	/* Check if we can use the interrupt */
	writel(CCN_MN_ERRINT_STATUS__PMU_EVENTS__DISABLE,
			ccn->base + CCN_MN_ERRINT_STATUS);
	if (readl(ccn->base + CCN_MN_ERRINT_STATUS) &
			CCN_MN_ERRINT_STATUS__PMU_EVENTS__DISABLED) {
		/* Can set 'disable' bits, so can acknowledge interrupts */
		writel(CCN_MN_ERRINT_STATUS__PMU_EVENTS__ENABLE,
				ccn->base + CCN_MN_ERRINT_STATUS);
		err = devm_request_irq(ccn->dev, irq, arm_ccn_irq_handler,
				       IRQF_NOBALANCING | IRQF_NO_THREAD,
				       dev_name(ccn->dev), ccn);
		if (err)
			return err;

		ccn->irq = irq;
	}


	/* Build topology */

	err = arm_ccn_for_each_valid_region(ccn, arm_ccn_get_nodes_num);
	if (err)
		return err;

	ccn->node = devm_kcalloc(ccn->dev, ccn->num_nodes, sizeof(*ccn->node),
				 GFP_KERNEL);
	ccn->xp = devm_kcalloc(ccn->dev, ccn->num_xps, sizeof(*ccn->node),
			       GFP_KERNEL);
	if (!ccn->node || !ccn->xp)
		return -ENOMEM;

	err = arm_ccn_for_each_valid_region(ccn, arm_ccn_init_nodes);
	if (err)
		return err;

	return arm_ccn_pmu_init(ccn);
}