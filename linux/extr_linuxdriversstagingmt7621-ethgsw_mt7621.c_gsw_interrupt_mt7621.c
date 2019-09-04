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
struct mtk_eth {unsigned int* link; int /*<<< orphan*/ * netdev; scalar_t__ sw_priv; } ;
struct mt7620_gsw {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MT7530_PMSR_P (int) ; 
 int /*<<< orphan*/  MT7530_SYS_INT_STS ; 
 int mt7530_mdio_r32 (struct mt7620_gsw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7530_mdio_w32 (struct mt7620_gsw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static irqreturn_t gsw_interrupt_mt7621(int irq, void *_eth)
{
	struct mtk_eth *eth = (struct mtk_eth *)_eth;
	struct mt7620_gsw *gsw = (struct mt7620_gsw *)eth->sw_priv;
	u32 reg, i;

	reg = mt7530_mdio_r32(gsw, MT7530_SYS_INT_STS);

	for (i = 0; i < 5; i++) {
		unsigned int link;

		if ((reg & BIT(i)) == 0)
			continue;

		link = mt7530_mdio_r32(gsw, MT7530_PMSR_P(i)) & 0x1;

		if (link == eth->link[i])
			continue;

		eth->link[i] = link;
		if (link)
			netdev_info(*eth->netdev,
				    "port %d link up\n", i);
		else
			netdev_info(*eth->netdev,
				    "port %d link down\n", i);
	}

	mt7530_mdio_w32(gsw, MT7530_SYS_INT_STS, 0x1f);

	return IRQ_HANDLED;
}