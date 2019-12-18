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
struct spdif_dev_data {scalar_t__ axi_clk; scalar_t__ base; scalar_t__ aclk; int /*<<< orphan*/  chsts_q; scalar_t__ mode; } ;
struct snd_soc_dai_driver {int /*<<< orphan*/  name; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 scalar_t__ XSPDIF_SOFT_RESET_REG ; 
 int /*<<< orphan*/  XSPDIF_SOFT_RESET_VALUE ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct spdif_dev_data*) ; 
 scalar_t__ devm_clk_get (struct device*,char*) ; 
 struct spdif_dev_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct spdif_dev_data*) ; 
 int devm_snd_soc_register_component (struct device*,int /*<<< orphan*/ *,struct snd_soc_dai_driver*,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xlnx_spdif_component ; 
 struct snd_soc_dai_driver xlnx_spdif_rx_dai ; 
 struct snd_soc_dai_driver xlnx_spdif_tx_dai ; 
 int /*<<< orphan*/  xlnx_spdifrx_irq_handler ; 

__attribute__((used)) static int xlnx_spdif_probe(struct platform_device *pdev)
{
	int ret;
	struct resource *res;
	struct snd_soc_dai_driver *dai_drv;
	struct spdif_dev_data *ctx;

	struct device *dev = &pdev->dev;
	struct device_node *node = dev->of_node;

	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->axi_clk = devm_clk_get(dev, "s_axi_aclk");
	if (IS_ERR(ctx->axi_clk)) {
		ret = PTR_ERR(ctx->axi_clk);
		dev_err(dev, "failed to get s_axi_aclk(%d)\n", ret);
		return ret;
	}
	ret = clk_prepare_enable(ctx->axi_clk);
	if (ret) {
		dev_err(dev, "failed to enable s_axi_aclk(%d)\n", ret);
		return ret;
	}

	ctx->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(ctx->base)) {
		ret = PTR_ERR(ctx->base);
		goto clk_err;
	}
	ret = of_property_read_u32(node, "xlnx,spdif-mode", &ctx->mode);
	if (ret < 0) {
		dev_err(dev, "cannot get SPDIF mode\n");
		goto clk_err;
	}
	if (ctx->mode) {
		dai_drv = &xlnx_spdif_tx_dai;
	} else {
		res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
		if (!res) {
			dev_err(dev, "No IRQ resource found\n");
			ret = -ENODEV;
			goto clk_err;
		}
		ret = devm_request_irq(dev, res->start,
				       xlnx_spdifrx_irq_handler,
				       0, "XLNX_SPDIF_RX", ctx);
		if (ret) {
			dev_err(dev, "spdif rx irq request failed\n");
			ret = -ENODEV;
			goto clk_err;
		}

		init_waitqueue_head(&ctx->chsts_q);
		dai_drv = &xlnx_spdif_rx_dai;
	}

	ret = of_property_read_u32(node, "xlnx,aud_clk_i", &ctx->aclk);
	if (ret < 0) {
		dev_err(dev, "cannot get aud_clk_i value\n");
		goto clk_err;
	}

	dev_set_drvdata(dev, ctx);

	ret = devm_snd_soc_register_component(dev, &xlnx_spdif_component,
					      dai_drv, 1);
	if (ret) {
		dev_err(dev, "SPDIF component registration failed\n");
		goto clk_err;
	}

	writel(XSPDIF_SOFT_RESET_VALUE, ctx->base + XSPDIF_SOFT_RESET_REG);
	dev_info(dev, "%s DAI registered\n", dai_drv->name);

clk_err:
	clk_disable_unprepare(ctx->axi_clk);
	return ret;
}