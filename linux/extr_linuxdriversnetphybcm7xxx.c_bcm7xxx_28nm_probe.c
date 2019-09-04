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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct phy_device {TYPE_1__ mdio; struct bcm7xxx_phy_priv* priv; } ;
struct bcm7xxx_phy_priv {int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bcm_phy_get_sset_count (struct phy_device*) ; 
 int /*<<< orphan*/  devm_kcalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct bcm7xxx_phy_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm7xxx_28nm_probe(struct phy_device *phydev)
{
	struct bcm7xxx_phy_priv *priv;

	priv = devm_kzalloc(&phydev->mdio.dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	phydev->priv = priv;

	priv->stats = devm_kcalloc(&phydev->mdio.dev,
				   bcm_phy_get_sset_count(phydev), sizeof(u64),
				   GFP_KERNEL);
	if (!priv->stats)
		return -ENOMEM;

	return 0;
}