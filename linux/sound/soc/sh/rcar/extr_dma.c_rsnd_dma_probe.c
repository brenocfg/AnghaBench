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
struct rsnd_priv {struct rsnd_dma_ctrl* dma; } ;
struct rsnd_dma_ctrl {int /*<<< orphan*/  base; scalar_t__ dmapp_num; } ;
struct resource {int dummy; } ;
struct platform_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct rsnd_dma_ctrl* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem ; 
 int /*<<< orphan*/  mem_ops ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ rsnd_is_gen1 (struct rsnd_priv*) ; 
 int rsnd_mod_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct device* rsnd_priv_to_dev (struct rsnd_priv*) ; 
 struct platform_device* rsnd_priv_to_pdev (struct rsnd_priv*) ; 

int rsnd_dma_probe(struct rsnd_priv *priv)
{
	struct platform_device *pdev = rsnd_priv_to_pdev(priv);
	struct device *dev = rsnd_priv_to_dev(priv);
	struct rsnd_dma_ctrl *dmac;
	struct resource *res;

	/*
	 * for Gen1
	 */
	if (rsnd_is_gen1(priv))
		return 0;

	/*
	 * for Gen2 or later
	 */
	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "audmapp");
	dmac = devm_kzalloc(dev, sizeof(*dmac), GFP_KERNEL);
	if (!dmac || !res) {
		dev_err(dev, "dma allocate failed\n");
		return 0; /* it will be PIO mode */
	}

	dmac->dmapp_num = 0;
	dmac->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(dmac->base))
		return PTR_ERR(dmac->base);

	priv->dma = dmac;

	/* dummy mem mod for debug */
	return rsnd_mod_init(NULL, &mem, &mem_ops, NULL, 0, 0);
}