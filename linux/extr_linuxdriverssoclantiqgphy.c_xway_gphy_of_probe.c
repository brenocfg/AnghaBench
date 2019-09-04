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
typedef  int u32 ;
struct xway_gphy_priv {int /*<<< orphan*/  fw_name; int /*<<< orphan*/  gphy_reset2; int /*<<< orphan*/  gphy_reset; int /*<<< orphan*/  membase; int /*<<< orphan*/  gphy_clk_gate; } ;
struct xway_gphy_match_data {int /*<<< orphan*/  ge_firmware_name; int /*<<< orphan*/  fe_firmware_name; } ;
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROBE_DEFER ; 
#define  GPHY_MODE_FE 129 
#define  GPHY_MODE_GE 128 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int device_property_read_u32 (struct device*,char*,int*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 int /*<<< orphan*/  devm_reset_control_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_reset_control_get_optional (struct device*,char*) ; 
 struct xway_gphy_match_data* of_device_get_match_data (struct device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xway_gphy_of_probe(struct platform_device *pdev,
			      struct xway_gphy_priv *priv)
{
	struct device *dev = &pdev->dev;
	const struct xway_gphy_match_data *gphy_fw_name_cfg;
	u32 gphy_mode;
	int ret;
	struct resource *res_gphy;

	gphy_fw_name_cfg = of_device_get_match_data(dev);

	priv->gphy_clk_gate = devm_clk_get(dev, NULL);
	if (IS_ERR(priv->gphy_clk_gate)) {
		dev_err(dev, "Failed to lookup gate clock\n");
		return PTR_ERR(priv->gphy_clk_gate);
	}

	res_gphy = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->membase = devm_ioremap_resource(dev, res_gphy);
	if (IS_ERR(priv->membase))
		return PTR_ERR(priv->membase);

	priv->gphy_reset = devm_reset_control_get(dev, "gphy");
	if (IS_ERR(priv->gphy_reset)) {
		if (PTR_ERR(priv->gphy_reset) != -EPROBE_DEFER)
			dev_err(dev, "Failed to lookup gphy reset\n");
		return PTR_ERR(priv->gphy_reset);
	}

	priv->gphy_reset2 = devm_reset_control_get_optional(dev, "gphy2");
	if (IS_ERR(priv->gphy_reset2))
		return PTR_ERR(priv->gphy_reset2);

	ret = device_property_read_u32(dev, "lantiq,gphy-mode", &gphy_mode);
	/* Default to GE mode */
	if (ret)
		gphy_mode = GPHY_MODE_GE;

	switch (gphy_mode) {
	case GPHY_MODE_FE:
		priv->fw_name = gphy_fw_name_cfg->fe_firmware_name;
		break;
	case GPHY_MODE_GE:
		priv->fw_name = gphy_fw_name_cfg->ge_firmware_name;
		break;
	default:
		dev_err(dev, "Unknown GPHY mode %d\n", gphy_mode);
		return -EINVAL;
	}

	return 0;
}