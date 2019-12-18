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
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct ep93xx_ac97_info {int /*<<< orphan*/ * dev; int /*<<< orphan*/  done; int /*<<< orphan*/  lock; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_TRIGGER_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct ep93xx_ac97_info*) ; 
 int devm_ep93xx_pcm_platform_register (int /*<<< orphan*/ *) ; 
 struct ep93xx_ac97_info* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ep93xx_ac97_info*) ; 
 int /*<<< orphan*/  ep93xx_ac97_component ; 
 int /*<<< orphan*/  ep93xx_ac97_dai ; 
 struct ep93xx_ac97_info* ep93xx_ac97_info ; 
 int /*<<< orphan*/  ep93xx_ac97_interrupt ; 
 int /*<<< orphan*/  ep93xx_ac97_ops ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ep93xx_ac97_info*) ; 
 int snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int snd_soc_set_ac97_ops (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_unregister_component (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ep93xx_ac97_probe(struct platform_device *pdev)
{
	struct ep93xx_ac97_info *info;
	int irq;
	int ret;

	info = devm_kzalloc(&pdev->dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->regs = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(info->regs))
		return PTR_ERR(info->regs);

	irq = platform_get_irq(pdev, 0);
	if (irq <= 0)
		return irq < 0 ? irq : -ENODEV;

	ret = devm_request_irq(&pdev->dev, irq, ep93xx_ac97_interrupt,
			       IRQF_TRIGGER_HIGH, pdev->name, info);
	if (ret)
		goto fail;

	dev_set_drvdata(&pdev->dev, info);

	mutex_init(&info->lock);
	init_completion(&info->done);
	info->dev = &pdev->dev;

	ep93xx_ac97_info = info;
	platform_set_drvdata(pdev, info);

	ret = snd_soc_set_ac97_ops(&ep93xx_ac97_ops);
	if (ret)
		goto fail;

	ret = snd_soc_register_component(&pdev->dev, &ep93xx_ac97_component,
					 &ep93xx_ac97_dai, 1);
	if (ret)
		goto fail;

	ret = devm_ep93xx_pcm_platform_register(&pdev->dev);
	if (ret)
		goto fail_unregister;

	return 0;

fail_unregister:
	snd_soc_unregister_component(&pdev->dev);
fail:
	ep93xx_ac97_info = NULL;
	snd_soc_set_ac97_ops(NULL);
	return ret;
}