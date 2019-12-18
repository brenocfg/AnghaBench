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
struct sprd_mcdt_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/ * dev; int /*<<< orphan*/  base; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct sprd_mcdt_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct sprd_mcdt_dev*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sprd_mcdt_dev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprd_mcdt_init_chans (struct sprd_mcdt_dev*,struct resource*) ; 
 int /*<<< orphan*/  sprd_mcdt_irq_handler ; 

__attribute__((used)) static int sprd_mcdt_probe(struct platform_device *pdev)
{
	struct sprd_mcdt_dev *mcdt;
	struct resource *res;
	int ret, irq;

	mcdt = devm_kzalloc(&pdev->dev, sizeof(*mcdt), GFP_KERNEL);
	if (!mcdt)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	mcdt->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(mcdt->base))
		return PTR_ERR(mcdt->base);

	mcdt->dev = &pdev->dev;
	spin_lock_init(&mcdt->lock);
	platform_set_drvdata(pdev, mcdt);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	ret = devm_request_irq(&pdev->dev, irq, sprd_mcdt_irq_handler,
			       0, "sprd-mcdt", mcdt);
	if (ret) {
		dev_err(&pdev->dev, "Failed to request MCDT IRQ\n");
		return ret;
	}

	sprd_mcdt_init_chans(mcdt, res);

	return 0;
}