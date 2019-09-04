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
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct phy_provider {int dummy; } ;
struct phy {int dummy; } ;
struct bcm_kona_usb {struct phy* regs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct phy*) ; 
 int PTR_ERR (struct phy*) ; 
 int PTR_ERR_OR_ZERO (struct phy_provider*) ; 
 struct phy* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct bcm_kona_usb* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (struct device*,int /*<<< orphan*/ ) ; 
 struct phy* devm_phy_create (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 int /*<<< orphan*/  ops ; 
 int /*<<< orphan*/  phy_set_bus_width (struct phy*,int) ; 
 int /*<<< orphan*/  phy_set_drvdata (struct phy*,struct bcm_kona_usb*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct bcm_kona_usb*) ; 

__attribute__((used)) static int bcm_kona_usb2_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct bcm_kona_usb *phy;
	struct resource *res;
	struct phy *gphy;
	struct phy_provider *phy_provider;

	phy = devm_kzalloc(dev, sizeof(*phy), GFP_KERNEL);
	if (!phy)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	phy->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(phy->regs))
		return PTR_ERR(phy->regs);

	platform_set_drvdata(pdev, phy);

	gphy = devm_phy_create(dev, NULL, &ops);
	if (IS_ERR(gphy))
		return PTR_ERR(gphy);

	/* The Kona PHY supports an 8-bit wide UTMI interface */
	phy_set_bus_width(gphy, 8);

	phy_set_drvdata(gphy, phy);

	phy_provider = devm_of_phy_provider_register(dev,
			of_phy_simple_xlate);

	return PTR_ERR_OR_ZERO(phy_provider);
}