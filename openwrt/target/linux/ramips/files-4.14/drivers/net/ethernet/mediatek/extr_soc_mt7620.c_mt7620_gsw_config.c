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
struct mt7620_gsw {int /*<<< orphan*/ * base; } ;
struct fe_priv {int /*<<< orphan*/  dev; int /*<<< orphan*/ * mii_bus; TYPE_1__* soc; } ;
struct TYPE_2__ {scalar_t__ swpriv; } ;

/* Variables and functions */
 scalar_t__ mdiobus_get_phy (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mt7530_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mt7620_gsw_config(struct fe_priv *priv)
{
	struct mt7620_gsw *gsw = (struct mt7620_gsw *) priv->soc->swpriv;

	/* is the mt7530 internal or external */
	if (priv->mii_bus && mdiobus_get_phy(priv->mii_bus, 0x1f)) {
		mt7530_probe(priv->dev, gsw->base, NULL, 0);
		mt7530_probe(priv->dev, NULL, priv->mii_bus, 1);
	} else {
		mt7530_probe(priv->dev, gsw->base, NULL, 1);
	}

	return 0;
}