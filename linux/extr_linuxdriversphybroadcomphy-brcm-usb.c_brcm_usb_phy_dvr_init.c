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
struct phy {int dummy; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct brcm_usb_phy_data {struct phy* usb_30_clk; TYPE_1__* phys; scalar_t__ has_xhci; scalar_t__ has_eohci; struct phy* usb_20_clk; } ;
struct TYPE_2__ {size_t id; struct phy* phy; } ;

/* Variables and functions */
 size_t BRCM_USB_PHY_2_0 ; 
 size_t BRCM_USB_PHY_3_0 ; 
 scalar_t__ IS_ERR (struct phy*) ; 
 int PTR_ERR (struct phy*) ; 
 int /*<<< orphan*/  brcm_usb_phy_ops ; 
 int clk_prepare_enable (struct phy*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 struct phy* devm_phy_create (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* of_clk_get_by_name (struct device_node*,char*) ; 
 int /*<<< orphan*/  phy_set_drvdata (struct phy*,TYPE_1__*) ; 

__attribute__((used)) static int brcm_usb_phy_dvr_init(struct device *dev,
				 struct brcm_usb_phy_data *priv,
				 struct device_node *dn)
{
	struct phy *gphy;
	int err;

	priv->usb_20_clk = of_clk_get_by_name(dn, "sw_usb");
	if (IS_ERR(priv->usb_20_clk)) {
		dev_info(dev, "Clock not found in Device Tree\n");
		priv->usb_20_clk = NULL;
	}
	err = clk_prepare_enable(priv->usb_20_clk);
	if (err)
		return err;

	if (priv->has_eohci) {
		gphy = devm_phy_create(dev, NULL, &brcm_usb_phy_ops);
		if (IS_ERR(gphy)) {
			dev_err(dev, "failed to create EHCI/OHCI PHY\n");
			return PTR_ERR(gphy);
		}
		priv->phys[BRCM_USB_PHY_2_0].phy = gphy;
		priv->phys[BRCM_USB_PHY_2_0].id = BRCM_USB_PHY_2_0;
		phy_set_drvdata(gphy, &priv->phys[BRCM_USB_PHY_2_0]);
	}

	if (priv->has_xhci) {
		gphy = devm_phy_create(dev, NULL, &brcm_usb_phy_ops);
		if (IS_ERR(gphy)) {
			dev_err(dev, "failed to create XHCI PHY\n");
			return PTR_ERR(gphy);
		}
		priv->phys[BRCM_USB_PHY_3_0].phy = gphy;
		priv->phys[BRCM_USB_PHY_3_0].id = BRCM_USB_PHY_3_0;
		phy_set_drvdata(gphy, &priv->phys[BRCM_USB_PHY_3_0]);

		priv->usb_30_clk = of_clk_get_by_name(dn, "sw_usb3");
		if (IS_ERR(priv->usb_30_clk)) {
			dev_info(dev,
				 "USB3.0 clock not found in Device Tree\n");
			priv->usb_30_clk = NULL;
		}
		err = clk_prepare_enable(priv->usb_30_clk);
		if (err)
			return err;
	}
	return 0;
}