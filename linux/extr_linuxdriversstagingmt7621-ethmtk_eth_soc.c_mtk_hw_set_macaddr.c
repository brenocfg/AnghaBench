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
struct mtk_mac {TYPE_1__* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  page_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_GDMA1_MAC_ADRH ; 
 int /*<<< orphan*/  MTK_GDMA1_MAC_ADRL ; 
 int /*<<< orphan*/  mtk_w32 (TYPE_1__*,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void mtk_hw_set_macaddr(struct mtk_mac *mac,
				      unsigned char *macaddr)
{
	unsigned long flags;

	spin_lock_irqsave(&mac->hw->page_lock, flags);
	mtk_w32(mac->hw, (macaddr[0] << 8) | macaddr[1], MTK_GDMA1_MAC_ADRH);
	mtk_w32(mac->hw, (macaddr[2] << 24) | (macaddr[3] << 16) |
		(macaddr[4] << 8) | macaddr[5],
		MTK_GDMA1_MAC_ADRL);
	spin_unlock_irqrestore(&mac->hw->page_lock, flags);
}