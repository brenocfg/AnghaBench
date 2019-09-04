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
struct smsc_phy_priv {int energy_enable; } ;
struct device {struct device_node* of_node; } ;
struct TYPE_2__ {struct device dev; } ;
struct phy_device {struct smsc_phy_priv* priv; TYPE_1__ mdio; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct smsc_phy_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 

__attribute__((used)) static int smsc_phy_probe(struct phy_device *phydev)
{
	struct device *dev = &phydev->mdio.dev;
	struct device_node *of_node = dev->of_node;
	struct smsc_phy_priv *priv;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->energy_enable = true;

	if (of_property_read_bool(of_node, "smsc,disable-energy-detect"))
		priv->energy_enable = false;

	phydev->priv = priv;

	return 0;
}