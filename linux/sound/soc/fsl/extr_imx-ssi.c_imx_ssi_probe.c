#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai_driver {int dummy; } ;
struct resource {scalar_t__ start; } ;
struct TYPE_13__ {struct imx_ssi_platform_data* platform_data; } ;
struct platform_device {TYPE_3__ dev; } ;
struct imx_ssi_platform_data {int flags; int /*<<< orphan*/  ac97_warm_reset; int /*<<< orphan*/  ac97_reset; } ;
struct TYPE_14__ {int irq; TYPE_2__* dma_params_tx; TYPE_1__* dma_params_rx; scalar_t__ base; } ;
struct TYPE_12__ {int maxburst; int /*<<< orphan*/ * filter_data; scalar_t__ addr; } ;
struct TYPE_11__ {int maxburst; int /*<<< orphan*/ * filter_data; scalar_t__ addr; } ;
struct imx_ssi {int flags; scalar_t__ irq; int fiq_init; scalar_t__ clk; scalar_t__ dma_init; TYPE_5__ fiq_params; TYPE_2__ dma_params_tx; TYPE_1__ dma_params_rx; scalar_t__ base; int /*<<< orphan*/  filter_data_rx; int /*<<< orphan*/  filter_data_tx; int /*<<< orphan*/  ac97_warm_reset; int /*<<< orphan*/  ac97_reset; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IMX_DMATYPE_SSI ; 
 int /*<<< orphan*/  IMX_SSI_DMABUF_SIZE ; 
 int IMX_SSI_USE_AC97 ; 
 int /*<<< orphan*/  IORESOURCE_DMA ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 scalar_t__ SSI_SIER ; 
 scalar_t__ SSI_SRX0 ; 
 scalar_t__ SSI_STX0 ; 
 struct imx_ssi* ac97_ssi ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_3__*,struct imx_ssi*) ; 
 scalar_t__ devm_clk_get (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 struct imx_ssi* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 struct snd_soc_dai_driver imx_ac97_dai ; 
 int /*<<< orphan*/  imx_component ; 
 scalar_t__ imx_pcm_dma_init (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_pcm_dma_params_init_data (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int imx_pcm_fiq_init (struct platform_device*,TYPE_5__*) ; 
 int /*<<< orphan*/  imx_ssi_ac97_ops ; 
 struct snd_soc_dai_driver imx_ssi_dai ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct imx_ssi*) ; 
 int /*<<< orphan*/  setup_channel_to_ac97 (struct imx_ssi*) ; 
 int snd_soc_register_component (TYPE_3__*,int /*<<< orphan*/ *,struct snd_soc_dai_driver*,int) ; 
 int snd_soc_set_ac97_ops (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_unregister_component (TYPE_3__*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int imx_ssi_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct imx_ssi *ssi;
	struct imx_ssi_platform_data *pdata = pdev->dev.platform_data;
	int ret = 0;
	struct snd_soc_dai_driver *dai;

	ssi = devm_kzalloc(&pdev->dev, sizeof(*ssi), GFP_KERNEL);
	if (!ssi)
		return -ENOMEM;
	dev_set_drvdata(&pdev->dev, ssi);

	if (pdata) {
		ssi->ac97_reset = pdata->ac97_reset;
		ssi->ac97_warm_reset = pdata->ac97_warm_reset;
		ssi->flags = pdata->flags;
	}

	ssi->irq = platform_get_irq(pdev, 0);
	if (ssi->irq < 0)
		return ssi->irq;

	ssi->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(ssi->clk)) {
		ret = PTR_ERR(ssi->clk);
		dev_err(&pdev->dev, "Cannot get the clock: %d\n",
			ret);
		goto failed_clk;
	}
	ret = clk_prepare_enable(ssi->clk);
	if (ret)
		goto failed_clk;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	ssi->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(ssi->base)) {
		ret = PTR_ERR(ssi->base);
		goto failed_register;
	}

	if (ssi->flags & IMX_SSI_USE_AC97) {
		if (ac97_ssi) {
			dev_err(&pdev->dev, "AC'97 SSI already registered\n");
			ret = -EBUSY;
			goto failed_register;
		}
		ac97_ssi = ssi;
		setup_channel_to_ac97(ssi);
		dai = &imx_ac97_dai;
	} else
		dai = &imx_ssi_dai;

	writel(0x0, ssi->base + SSI_SIER);

	ssi->dma_params_rx.addr = res->start + SSI_SRX0;
	ssi->dma_params_tx.addr = res->start + SSI_STX0;

	ssi->dma_params_tx.maxburst = 6;
	ssi->dma_params_rx.maxburst = 4;

	ssi->dma_params_tx.filter_data = &ssi->filter_data_tx;
	ssi->dma_params_rx.filter_data = &ssi->filter_data_rx;

	res = platform_get_resource_byname(pdev, IORESOURCE_DMA, "tx0");
	if (res) {
		imx_pcm_dma_params_init_data(&ssi->filter_data_tx, res->start,
			IMX_DMATYPE_SSI);
	}

	res = platform_get_resource_byname(pdev, IORESOURCE_DMA, "rx0");
	if (res) {
		imx_pcm_dma_params_init_data(&ssi->filter_data_rx, res->start,
			IMX_DMATYPE_SSI);
	}

	platform_set_drvdata(pdev, ssi);

	ret = snd_soc_set_ac97_ops(&imx_ssi_ac97_ops);
	if (ret != 0) {
		dev_err(&pdev->dev, "Failed to set AC'97 ops: %d\n", ret);
		goto failed_register;
	}

	ret = snd_soc_register_component(&pdev->dev, &imx_component,
					 dai, 1);
	if (ret) {
		dev_err(&pdev->dev, "register DAI failed\n");
		goto failed_register;
	}

	ssi->fiq_params.irq = ssi->irq;
	ssi->fiq_params.base = ssi->base;
	ssi->fiq_params.dma_params_rx = &ssi->dma_params_rx;
	ssi->fiq_params.dma_params_tx = &ssi->dma_params_tx;

	ssi->fiq_init = imx_pcm_fiq_init(pdev, &ssi->fiq_params);
	ssi->dma_init = imx_pcm_dma_init(pdev, IMX_SSI_DMABUF_SIZE);

	if (ssi->fiq_init && ssi->dma_init) {
		ret = ssi->fiq_init;
		goto failed_pcm;
	}

	return 0;

failed_pcm:
	snd_soc_unregister_component(&pdev->dev);
failed_register:
	clk_disable_unprepare(ssi->clk);
failed_clk:
	snd_soc_set_ac97_ops(NULL);

	return ret;
}