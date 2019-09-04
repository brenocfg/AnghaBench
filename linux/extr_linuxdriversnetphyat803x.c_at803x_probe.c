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
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;
struct phy_device {struct at803x_priv* priv; TYPE_1__ mdio; } ;
struct at803x_priv {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct at803x_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int at803x_probe(struct phy_device *phydev)
{
	struct device *dev = &phydev->mdio.dev;
	struct at803x_priv *priv;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	phydev->priv = priv;

	return 0;
}