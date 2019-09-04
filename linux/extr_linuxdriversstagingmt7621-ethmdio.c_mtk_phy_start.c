#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mtk_mac {struct mtk_eth* hw; } ;
struct mtk_eth {int* link; TYPE_2__* phy; TYPE_1__* soc; } ;
struct TYPE_4__ {scalar_t__* phy; int /*<<< orphan*/  lock; scalar_t__* phy_fixed; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* mdio_adjust_link ) (struct mtk_eth*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  phy_start (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct mtk_eth*,int) ; 

__attribute__((used)) static void mtk_phy_start(struct mtk_mac *mac)
{
	struct mtk_eth *eth = mac->hw;
	unsigned long flags;
	int i;

	for (i = 0; i < 8; i++) {
		if (eth->phy->phy_fixed[i]) {
			spin_lock_irqsave(&eth->phy->lock, flags);
			eth->link[i] = 1;
			if (eth->soc->mdio_adjust_link)
				eth->soc->mdio_adjust_link(eth, i);
			spin_unlock_irqrestore(&eth->phy->lock, flags);
		} else if (eth->phy->phy[i]) {
			phy_start(eth->phy->phy[i]);
		}
	}
}