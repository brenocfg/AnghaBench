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
struct resource {scalar_t__ start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {char* filter_data; scalar_t__ addr; } ;
struct omap_dmic {int /*<<< orphan*/  io_base; TYPE_1__ dma_data; int /*<<< orphan*/ * dev; int /*<<< orphan*/  fclk; int /*<<< orphan*/  mutex; int /*<<< orphan*/  sysclk; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ OMAP_DMIC_DATA_REG ; 
 int /*<<< orphan*/  OMAP_DMIC_SYSCLK_SYNC_MUX_CLKS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct omap_dmic* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_dmic_component ; 
 int /*<<< orphan*/  omap_dmic_dai ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct omap_dmic*) ; 
 int sdma_pcm_platform_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int asoc_dmic_probe(struct platform_device *pdev)
{
	struct omap_dmic *dmic;
	struct resource *res;
	int ret;

	dmic = devm_kzalloc(&pdev->dev, sizeof(struct omap_dmic), GFP_KERNEL);
	if (!dmic)
		return -ENOMEM;

	platform_set_drvdata(pdev, dmic);
	dmic->dev = &pdev->dev;
	dmic->sysclk = OMAP_DMIC_SYSCLK_SYNC_MUX_CLKS;

	mutex_init(&dmic->mutex);

	dmic->fclk = devm_clk_get(dmic->dev, "fck");
	if (IS_ERR(dmic->fclk)) {
		dev_err(dmic->dev, "cant get fck\n");
		return -ENODEV;
	}

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "dma");
	if (!res) {
		dev_err(dmic->dev, "invalid dma memory resource\n");
		return -ENODEV;
	}
	dmic->dma_data.addr = res->start + OMAP_DMIC_DATA_REG;

	dmic->dma_data.filter_data = "up_link";

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "mpu");
	dmic->io_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(dmic->io_base))
		return PTR_ERR(dmic->io_base);


	ret = devm_snd_soc_register_component(&pdev->dev,
					      &omap_dmic_component,
					      &omap_dmic_dai, 1);
	if (ret)
		return ret;

	ret = sdma_pcm_platform_register(&pdev->dev, NULL, "up_link");
	if (ret)
		return ret;

	return 0;
}