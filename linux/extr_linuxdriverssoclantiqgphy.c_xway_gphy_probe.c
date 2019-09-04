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
struct xway_gphy_priv {int /*<<< orphan*/  gphy_reset2; int /*<<< orphan*/  gphy_reset; int /*<<< orphan*/  membase; int /*<<< orphan*/  gphy_clk_gate; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct xway_gphy_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct xway_gphy_priv*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int xway_gphy_load (struct device*,struct xway_gphy_priv*,int /*<<< orphan*/ *) ; 
 int xway_gphy_of_probe (struct platform_device*,struct xway_gphy_priv*) ; 

__attribute__((used)) static int xway_gphy_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct xway_gphy_priv *priv;
	dma_addr_t fw_addr = 0;
	int ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	ret = xway_gphy_of_probe(pdev, priv);
	if (ret)
		return ret;

	ret = clk_prepare_enable(priv->gphy_clk_gate);
	if (ret)
		return ret;

	ret = xway_gphy_load(dev, priv, &fw_addr);
	if (ret) {
		clk_disable_unprepare(priv->gphy_clk_gate);
		return ret;
	}

	reset_control_assert(priv->gphy_reset);
	reset_control_assert(priv->gphy_reset2);

	iowrite32be(fw_addr, priv->membase);

	reset_control_deassert(priv->gphy_reset);
	reset_control_deassert(priv->gphy_reset2);

	platform_set_drvdata(pdev, priv);

	return ret;
}