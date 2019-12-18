#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai_driver {int dummy; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct au1xpsc_audio_data {int cfg; TYPE_1__ dai_drv; int /*<<< orphan*/ * dmaids; int /*<<< orphan*/  mmio; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_DMA ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PSC_AC97CFG_DE_ENABLE ; 
 int PSC_AC97CFG_RT_FIFO8 ; 
 int PSC_AC97CFG_TT_FIFO8 ; 
 int /*<<< orphan*/  PSC_CTRL (struct au1xpsc_audio_data*) ; 
 unsigned long PSC_CTRL_DISABLE ; 
 int /*<<< orphan*/  PSC_SEL (struct au1xpsc_audio_data*) ; 
 unsigned long PSC_SEL_CLK_MASK ; 
 unsigned long PSC_SEL_PS_AC97MODE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au1xpsc_ac97_component ; 
 int /*<<< orphan*/  au1xpsc_ac97_dai_template ; 
 struct au1xpsc_audio_data* au1xpsc_ac97_workdata ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 struct au1xpsc_audio_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct au1xpsc_audio_data*) ; 
 int /*<<< orphan*/  psc_ac97_ops ; 
 int snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int snd_soc_set_ac97_ops (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int au1xpsc_ac97_drvprobe(struct platform_device *pdev)
{
	int ret;
	struct resource *dmares;
	unsigned long sel;
	struct au1xpsc_audio_data *wd;

	wd = devm_kzalloc(&pdev->dev, sizeof(struct au1xpsc_audio_data),
			  GFP_KERNEL);
	if (!wd)
		return -ENOMEM;

	mutex_init(&wd->lock);

	wd->mmio = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(wd->mmio))
		return PTR_ERR(wd->mmio);

	dmares = platform_get_resource(pdev, IORESOURCE_DMA, 0);
	if (!dmares)
		return -EBUSY;
	wd->dmaids[SNDRV_PCM_STREAM_PLAYBACK] = dmares->start;

	dmares = platform_get_resource(pdev, IORESOURCE_DMA, 1);
	if (!dmares)
		return -EBUSY;
	wd->dmaids[SNDRV_PCM_STREAM_CAPTURE] = dmares->start;

	/* configuration: max dma trigger threshold, enable ac97 */
	wd->cfg = PSC_AC97CFG_RT_FIFO8 | PSC_AC97CFG_TT_FIFO8 |
		  PSC_AC97CFG_DE_ENABLE;

	/* preserve PSC clock source set up by platform	 */
	sel = __raw_readl(PSC_SEL(wd)) & PSC_SEL_CLK_MASK;
	__raw_writel(PSC_CTRL_DISABLE, PSC_CTRL(wd));
	wmb(); /* drain writebuffer */
	__raw_writel(0, PSC_SEL(wd));
	wmb(); /* drain writebuffer */
	__raw_writel(PSC_SEL_PS_AC97MODE | sel, PSC_SEL(wd));
	wmb(); /* drain writebuffer */

	/* name the DAI like this device instance ("au1xpsc-ac97.PSCINDEX") */
	memcpy(&wd->dai_drv, &au1xpsc_ac97_dai_template,
	       sizeof(struct snd_soc_dai_driver));
	wd->dai_drv.name = dev_name(&pdev->dev);

	platform_set_drvdata(pdev, wd);

	ret = snd_soc_set_ac97_ops(&psc_ac97_ops);
	if (ret)
		return ret;

	ret = snd_soc_register_component(&pdev->dev, &au1xpsc_ac97_component,
					 &wd->dai_drv, 1);
	if (ret)
		return ret;

	au1xpsc_ac97_workdata = wd;
	return 0;
}