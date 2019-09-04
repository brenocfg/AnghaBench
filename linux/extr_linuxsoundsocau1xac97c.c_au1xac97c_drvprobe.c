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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct au1xpsc_audio_data {int cfg; int /*<<< orphan*/ * dmaids; int /*<<< orphan*/  mmio; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_CONFIG ; 
 int /*<<< orphan*/  AC97_ENABLE ; 
 int CFG_RC (int) ; 
 int CFG_XS (int) ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EN_CE ; 
 int EN_D ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_DMA ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  WR (struct au1xpsc_audio_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ac97c_bus_ops ; 
 struct au1xpsc_audio_data* ac97c_workdata ; 
 int /*<<< orphan*/  au1xac97c_component ; 
 int /*<<< orphan*/  au1xac97c_dai_driver ; 
 int /*<<< orphan*/  devm_ioremap_nocache (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct au1xpsc_audio_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_request_mem_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct au1xpsc_audio_data*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int snd_soc_set_ac97_ops (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int au1xac97c_drvprobe(struct platform_device *pdev)
{
	int ret;
	struct resource *iores, *dmares;
	struct au1xpsc_audio_data *ctx;

	ctx = devm_kzalloc(&pdev->dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	mutex_init(&ctx->lock);

	iores = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!iores)
		return -ENODEV;

	if (!devm_request_mem_region(&pdev->dev, iores->start,
				     resource_size(iores),
				     pdev->name))
		return -EBUSY;

	ctx->mmio = devm_ioremap_nocache(&pdev->dev, iores->start,
					 resource_size(iores));
	if (!ctx->mmio)
		return -EBUSY;

	dmares = platform_get_resource(pdev, IORESOURCE_DMA, 0);
	if (!dmares)
		return -EBUSY;
	ctx->dmaids[SNDRV_PCM_STREAM_PLAYBACK] = dmares->start;

	dmares = platform_get_resource(pdev, IORESOURCE_DMA, 1);
	if (!dmares)
		return -EBUSY;
	ctx->dmaids[SNDRV_PCM_STREAM_CAPTURE] = dmares->start;

	/* switch it on */
	WR(ctx, AC97_ENABLE, EN_D | EN_CE);
	WR(ctx, AC97_ENABLE, EN_CE);

	ctx->cfg = CFG_RC(3) | CFG_XS(3);
	WR(ctx, AC97_CONFIG, ctx->cfg);

	platform_set_drvdata(pdev, ctx);

	ret = snd_soc_set_ac97_ops(&ac97c_bus_ops);
	if (ret)
		return ret;

	ret = snd_soc_register_component(&pdev->dev, &au1xac97c_component,
					 &au1xac97c_dai_driver, 1);
	if (ret)
		return ret;

	ac97c_workdata = ctx;
	return 0;
}