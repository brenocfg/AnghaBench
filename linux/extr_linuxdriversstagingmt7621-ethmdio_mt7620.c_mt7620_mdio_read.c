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
struct mtk_eth {scalar_t__ sw_priv; } ;
struct mt7620_gsw {int dummy; } ;
struct mii_bus {struct mtk_eth* priv; } ;

/* Variables and functions */
 int _mt7620_mii_read (struct mt7620_gsw*,int,int) ; 

int mt7620_mdio_read(struct mii_bus *bus, int phy_addr, int phy_reg)
{
	struct mtk_eth *eth = bus->priv;
	struct mt7620_gsw *gsw = (struct mt7620_gsw *)eth->sw_priv;

	return _mt7620_mii_read(gsw, phy_addr, phy_reg);
}