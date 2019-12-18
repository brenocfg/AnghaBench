#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mxs_saif {int id; int master_id; TYPE_1__* dev; int /*<<< orphan*/  base; int /*<<< orphan*/  clk; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct mxs_saif**) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct mxs_saif* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mxs_saif*) ; 
 int devm_snd_soc_register_component (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int mxs_pcm_platform_register (TYPE_1__*) ; 
 struct mxs_saif** mxs_saif ; 
 int /*<<< orphan*/  mxs_saif_component ; 
 int /*<<< orphan*/  mxs_saif_dai ; 
 int /*<<< orphan*/  mxs_saif_irq ; 
 int mxs_saif_mclk_init (struct platform_device*) ; 
 int of_alias_get_id (struct device_node*,char*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mxs_saif*) ; 

__attribute__((used)) static int mxs_saif_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct mxs_saif *saif;
	int irq, ret = 0;
	struct device_node *master;

	if (!np)
		return -EINVAL;

	saif = devm_kzalloc(&pdev->dev, sizeof(*saif), GFP_KERNEL);
	if (!saif)
		return -ENOMEM;

	ret = of_alias_get_id(np, "saif");
	if (ret < 0)
		return ret;
	else
		saif->id = ret;

	if (saif->id >= ARRAY_SIZE(mxs_saif)) {
		dev_err(&pdev->dev, "get wrong saif id\n");
		return -EINVAL;
	}

	/*
	 * If there is no "fsl,saif-master" phandle, it's a saif
	 * master.  Otherwise, it's a slave and its phandle points
	 * to the master.
	 */
	master = of_parse_phandle(np, "fsl,saif-master", 0);
	if (!master) {
		saif->master_id = saif->id;
	} else {
		ret = of_alias_get_id(master, "saif");
		if (ret < 0)
			return ret;
		else
			saif->master_id = ret;

		if (saif->master_id >= ARRAY_SIZE(mxs_saif)) {
			dev_err(&pdev->dev, "get wrong master id\n");
			return -EINVAL;
		}
	}

	mxs_saif[saif->id] = saif;

	saif->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(saif->clk)) {
		ret = PTR_ERR(saif->clk);
		dev_err(&pdev->dev, "Cannot get the clock: %d\n",
			ret);
		return ret;
	}

	saif->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(saif->base))
		return PTR_ERR(saif->base);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	saif->dev = &pdev->dev;
	ret = devm_request_irq(&pdev->dev, irq, mxs_saif_irq, 0,
			       dev_name(&pdev->dev), saif);
	if (ret) {
		dev_err(&pdev->dev, "failed to request irq\n");
		return ret;
	}

	platform_set_drvdata(pdev, saif);

	/* We only support saif0 being tx and clock master */
	if (saif->id == 0) {
		ret = mxs_saif_mclk_init(pdev);
		if (ret)
			dev_warn(&pdev->dev, "failed to init clocks\n");
	}

	ret = devm_snd_soc_register_component(&pdev->dev, &mxs_saif_component,
					      &mxs_saif_dai, 1);
	if (ret) {
		dev_err(&pdev->dev, "register DAI failed\n");
		return ret;
	}

	ret = mxs_pcm_platform_register(&pdev->dev);
	if (ret) {
		dev_err(&pdev->dev, "register PCM failed: %d\n", ret);
		return ret;
	}

	return 0;
}