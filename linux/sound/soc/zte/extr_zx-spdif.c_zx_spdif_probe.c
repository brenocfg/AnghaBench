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
struct zx_spdif_info {int /*<<< orphan*/  reg_base; int /*<<< orphan*/  mapbase; int /*<<< orphan*/  dai_clk; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct zx_spdif_info* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_snd_dmaengine_pcm_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct zx_spdif_info*) ; 
 int /*<<< orphan*/  zx_spdif_component ; 
 int /*<<< orphan*/  zx_spdif_dai ; 
 int /*<<< orphan*/  zx_spdif_dev_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zx_spdif_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct zx_spdif_info *zx_spdif;
	int ret;

	zx_spdif = devm_kzalloc(&pdev->dev, sizeof(*zx_spdif), GFP_KERNEL);
	if (!zx_spdif)
		return -ENOMEM;

	zx_spdif->dai_clk = devm_clk_get(&pdev->dev, "tx");
	if (IS_ERR(zx_spdif->dai_clk)) {
		dev_err(&pdev->dev, "Fail to get clk\n");
		return PTR_ERR(zx_spdif->dai_clk);
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	zx_spdif->mapbase = res->start;
	zx_spdif->reg_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(zx_spdif->reg_base)) {
		dev_err(&pdev->dev, "ioremap failed!\n");
		return PTR_ERR(zx_spdif->reg_base);
	}

	zx_spdif_dev_init(zx_spdif->reg_base);
	platform_set_drvdata(pdev, zx_spdif);

	ret = devm_snd_soc_register_component(&pdev->dev, &zx_spdif_component,
					 &zx_spdif_dai, 1);
	if (ret) {
		dev_err(&pdev->dev, "Register DAI failed: %d\n", ret);
		return ret;
	}

	ret = devm_snd_dmaengine_pcm_register(&pdev->dev, NULL, 0);
	if (ret)
		dev_err(&pdev->dev, "Register platform PCM failed: %d\n", ret);

	return ret;
}