#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai_driver {int dummy; } ;
struct TYPE_8__ {struct device_node* of_node; struct kirkwood_asoc_platform_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct kirkwood_dma_data {scalar_t__ irq; int burst; void* clk; void* extclk; int /*<<< orphan*/  ctl_rec; int /*<<< orphan*/  ctl_play; void* io; } ;
struct kirkwood_asoc_platform_data {int burst; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 void* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  KIRKWOOD_PLAYCTL_BURST_128 ; 
 int /*<<< orphan*/  KIRKWOOD_PLAYCTL_BURST_32 ; 
 int /*<<< orphan*/  KIRKWOOD_PLAYCTL_SIZE_24 ; 
 int /*<<< orphan*/  KIRKWOOD_RECCTL_BURST_128 ; 
 int /*<<< orphan*/  KIRKWOOD_RECCTL_BURST_32 ; 
 int /*<<< orphan*/  KIRKWOOD_RECCTL_SIZE_24 ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 scalar_t__ clk_is_match (void*,void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct kirkwood_dma_data*) ; 
 void* devm_clk_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_clk_put (TYPE_1__*,void*) ; 
 struct kirkwood_dma_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 void* devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct snd_soc_dai_driver* kirkwood_i2s_dai ; 
 struct snd_soc_dai_driver* kirkwood_i2s_dai_extclk ; 
 int /*<<< orphan*/  kirkwood_i2s_init (struct kirkwood_dma_data*) ; 
 int /*<<< orphan*/  kirkwood_soc_component ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int snd_soc_register_component (TYPE_1__*,int /*<<< orphan*/ *,struct snd_soc_dai_driver*,int) ; 

__attribute__((used)) static int kirkwood_i2s_dev_probe(struct platform_device *pdev)
{
	struct kirkwood_asoc_platform_data *data = pdev->dev.platform_data;
	struct snd_soc_dai_driver *soc_dai = kirkwood_i2s_dai;
	struct kirkwood_dma_data *priv;
	struct device_node *np = pdev->dev.of_node;
	int err;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	dev_set_drvdata(&pdev->dev, priv);

	priv->io = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(priv->io))
		return PTR_ERR(priv->io);

	priv->irq = platform_get_irq(pdev, 0);
	if (priv->irq < 0)
		return priv->irq;

	if (np) {
		priv->burst = 128;		/* might be 32 or 128 */
	} else if (data) {
		priv->burst = data->burst;
	} else {
		dev_err(&pdev->dev, "no DT nor platform data ?!\n");
		return -EINVAL;
	}

	priv->clk = devm_clk_get(&pdev->dev, np ? "internal" : NULL);
	if (IS_ERR(priv->clk)) {
		dev_err(&pdev->dev, "no clock\n");
		return PTR_ERR(priv->clk);
	}

	priv->extclk = devm_clk_get(&pdev->dev, "extclk");
	if (IS_ERR(priv->extclk)) {
		if (PTR_ERR(priv->extclk) == -EPROBE_DEFER)
			return -EPROBE_DEFER;
	} else {
		if (clk_is_match(priv->extclk, priv->clk)) {
			devm_clk_put(&pdev->dev, priv->extclk);
			priv->extclk = ERR_PTR(-EINVAL);
		} else {
			dev_info(&pdev->dev, "found external clock\n");
			clk_prepare_enable(priv->extclk);
			soc_dai = kirkwood_i2s_dai_extclk;
		}
	}

	err = clk_prepare_enable(priv->clk);
	if (err < 0)
		return err;

	/* Some sensible defaults - this reflects the powerup values */
	priv->ctl_play = KIRKWOOD_PLAYCTL_SIZE_24;
	priv->ctl_rec = KIRKWOOD_RECCTL_SIZE_24;

	/* Select the burst size */
	if (priv->burst == 32) {
		priv->ctl_play |= KIRKWOOD_PLAYCTL_BURST_32;
		priv->ctl_rec |= KIRKWOOD_RECCTL_BURST_32;
	} else {
		priv->ctl_play |= KIRKWOOD_PLAYCTL_BURST_128;
		priv->ctl_rec |= KIRKWOOD_RECCTL_BURST_128;
	}

	err = snd_soc_register_component(&pdev->dev, &kirkwood_soc_component,
					 soc_dai, 2);
	if (err) {
		dev_err(&pdev->dev, "snd_soc_register_component failed\n");
		goto err_component;
	}

	kirkwood_i2s_init(priv);

	return 0;

 err_component:
	if (!IS_ERR(priv->extclk))
		clk_disable_unprepare(priv->extclk);
	clk_disable_unprepare(priv->clk);

	return err;
}