#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct spear_spdif_platform_data {int /*<<< orphan*/  filter; int /*<<< orphan*/  dma_params; } ;
struct TYPE_2__ {int max_burst; int /*<<< orphan*/  addr_width; scalar_t__ addr; int /*<<< orphan*/  data; } ;
struct spdif_out_dev {int /*<<< orphan*/  config; TYPE_1__ dma_params; int /*<<< orphan*/  clk; int /*<<< orphan*/  io_base; } ;
struct resource {scalar_t__ start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SPDIF_OUT_FIFO_DATA ; 
 struct spear_spdif_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct spdif_out_dev*) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct spdif_out_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int devm_spear_pcm_platform_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spdif_out_component ; 
 int /*<<< orphan*/  spdif_out_dai ; 

__attribute__((used)) static int spdif_out_probe(struct platform_device *pdev)
{
	struct spdif_out_dev *host;
	struct spear_spdif_platform_data *pdata;
	struct resource *res;
	int ret;

	host = devm_kzalloc(&pdev->dev, sizeof(*host), GFP_KERNEL);
	if (!host)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	host->io_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(host->io_base))
		return PTR_ERR(host->io_base);

	host->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(host->clk))
		return PTR_ERR(host->clk);

	pdata = dev_get_platdata(&pdev->dev);

	host->dma_params.data = pdata->dma_params;
	host->dma_params.addr = res->start + SPDIF_OUT_FIFO_DATA;
	host->dma_params.max_burst = 16;
	host->dma_params.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;

	dev_set_drvdata(&pdev->dev, host);

	ret = devm_snd_soc_register_component(&pdev->dev, &spdif_out_component,
					      &spdif_out_dai, 1);
	if (ret)
		return ret;

	return devm_spear_pcm_platform_register(&pdev->dev, &host->config,
						pdata->filter);
}