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
struct ep93xx_i2s_info {void* mclk; void* sclk; void* lrclk; void* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SND_EP93XX_SOC_I2S_WATCHDOG ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 void* clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clk_put (void*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct ep93xx_i2s_info*) ; 
 int devm_ep93xx_pcm_platform_register (int /*<<< orphan*/ *) ; 
 struct ep93xx_i2s_info* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 void* devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ep93xx_i2s_info*) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ep93xx_i2s_component ; 
 int /*<<< orphan*/  ep93xx_i2s_dai ; 
 int /*<<< orphan*/  ep93xx_i2s_interrupt ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ep93xx_i2s_probe(struct platform_device *pdev)
{
	struct ep93xx_i2s_info *info;
	int err;

	info = devm_kzalloc(&pdev->dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->regs = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(info->regs))
		return PTR_ERR(info->regs);

	if (IS_ENABLED(CONFIG_SND_EP93XX_SOC_I2S_WATCHDOG)) {
		int irq = platform_get_irq(pdev, 0);
		if (irq <= 0)
			return irq < 0 ? irq : -ENODEV;

		err = devm_request_irq(&pdev->dev, irq, ep93xx_i2s_interrupt, 0,
				       pdev->name, info);
		if (err)
			return err;
	}

	info->mclk = clk_get(&pdev->dev, "mclk");
	if (IS_ERR(info->mclk)) {
		err = PTR_ERR(info->mclk);
		goto fail;
	}

	info->sclk = clk_get(&pdev->dev, "sclk");
	if (IS_ERR(info->sclk)) {
		err = PTR_ERR(info->sclk);
		goto fail_put_mclk;
	}

	info->lrclk = clk_get(&pdev->dev, "lrclk");
	if (IS_ERR(info->lrclk)) {
		err = PTR_ERR(info->lrclk);
		goto fail_put_sclk;
	}

	dev_set_drvdata(&pdev->dev, info);

	err = devm_snd_soc_register_component(&pdev->dev, &ep93xx_i2s_component,
					 &ep93xx_i2s_dai, 1);
	if (err)
		goto fail_put_lrclk;

	err = devm_ep93xx_pcm_platform_register(&pdev->dev);
	if (err)
		goto fail_put_lrclk;

	return 0;

fail_put_lrclk:
	clk_put(info->lrclk);
fail_put_sclk:
	clk_put(info->sclk);
fail_put_mclk:
	clk_put(info->mclk);
fail:
	return err;
}