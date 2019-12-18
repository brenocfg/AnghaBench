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
struct txx9aclc_plat_drvdata {scalar_t__ physbase; int /*<<< orphan*/  base; } ;
struct resource {scalar_t__ start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ TXX9_DIRECTMAP_BASE ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct txx9aclc_plat_drvdata* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct txx9aclc_plat_drvdata*) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct txx9aclc_plat_drvdata*) ; 
 int snd_soc_set_ac97_ops (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txx9aclc_ac97_component ; 
 int /*<<< orphan*/  txx9aclc_ac97_dai ; 
 int /*<<< orphan*/  txx9aclc_ac97_irq ; 
 int /*<<< orphan*/  txx9aclc_ac97_ops ; 

__attribute__((used)) static int txx9aclc_ac97_dev_probe(struct platform_device *pdev)
{
	struct txx9aclc_plat_drvdata *drvdata;
	struct resource *r;
	int err;
	int irq;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	drvdata = devm_kzalloc(&pdev->dev, sizeof(*drvdata), GFP_KERNEL);
	if (!drvdata)
		return -ENOMEM;

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	drvdata->base = devm_ioremap_resource(&pdev->dev, r);
	if (IS_ERR(drvdata->base))
		return PTR_ERR(drvdata->base);

	platform_set_drvdata(pdev, drvdata);
	drvdata->physbase = r->start;
	if (sizeof(drvdata->physbase) > sizeof(r->start) &&
	    r->start >= TXX9_DIRECTMAP_BASE &&
	    r->start < TXX9_DIRECTMAP_BASE + 0x400000)
		drvdata->physbase |= 0xf00000000ull;
	err = devm_request_irq(&pdev->dev, irq, txx9aclc_ac97_irq,
			       0, dev_name(&pdev->dev), drvdata);
	if (err < 0)
		return err;

	err = snd_soc_set_ac97_ops(&txx9aclc_ac97_ops);
	if (err < 0)
		return err;

	return devm_snd_soc_register_component(&pdev->dev, &txx9aclc_ac97_component,
					  &txx9aclc_ac97_dai, 1);
}