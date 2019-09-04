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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct phy {int dummy; } ;
struct ath79_usb_phy {struct phy* no_suspend_override; struct phy* reset; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct phy*) ; 
 int PTR_ERR (struct phy*) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath79_usb_phy_ops ; 
 struct ath79_usb_phy* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_of_phy_provider_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct phy* devm_phy_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct phy* devm_reset_control_get (int /*<<< orphan*/ *,char*) ; 
 struct phy* devm_reset_control_get_optional (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 int /*<<< orphan*/  phy_set_drvdata (struct phy*,struct ath79_usb_phy*) ; 

__attribute__((used)) static int ath79_usb_phy_probe(struct platform_device *pdev)
{
	struct ath79_usb_phy *priv;
	struct phy *phy;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->reset = devm_reset_control_get(&pdev->dev, "phy");
	if (IS_ERR(priv->reset))
		return PTR_ERR(priv->reset);

	priv->no_suspend_override = devm_reset_control_get_optional(
		&pdev->dev, "usb-suspend-override");
	if (IS_ERR(priv->no_suspend_override))
		return PTR_ERR(priv->no_suspend_override);

	phy = devm_phy_create(&pdev->dev, NULL, &ath79_usb_phy_ops);
	if (IS_ERR(phy))
		return PTR_ERR(phy);

	phy_set_drvdata(phy, priv);

	return PTR_ERR_OR_ZERO(devm_of_phy_provider_register(
				&pdev->dev, of_phy_simple_xlate));
}