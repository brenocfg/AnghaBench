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
typedef  int /*<<< orphan*/  u16 ;
struct mt7620_gsw {int dummy; } ;
struct mii_bus {struct fe_priv* priv; } ;
struct fe_priv {TYPE_1__* soc; } ;
struct TYPE_2__ {scalar_t__ swpriv; } ;

/* Variables and functions */
 int _mt7620_mii_write (struct mt7620_gsw*,int,int,int /*<<< orphan*/ ) ; 

int mt7620_mdio_write(struct mii_bus *bus, int phy_addr, int phy_reg, u16 val)
{
	struct fe_priv *priv = bus->priv;
	struct mt7620_gsw *gsw = (struct mt7620_gsw *)priv->soc->swpriv;

	return _mt7620_mii_write(gsw, phy_addr, phy_reg, val);
}