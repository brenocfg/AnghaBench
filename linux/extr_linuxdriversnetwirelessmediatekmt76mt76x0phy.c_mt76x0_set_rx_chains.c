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
struct mt76x0_dev {int chainmask; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGC ; 
 int BIT (int) ; 
 int /*<<< orphan*/  MT_BBP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int mt76_rr (struct mt76x0_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x0_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mt76x0_set_rx_chains(struct mt76x0_dev *dev)
{
	u32 val;

	val = mt76_rr(dev, MT_BBP(AGC, 0));
	val &= ~(BIT(3) | BIT(4));

	if (dev->chainmask & BIT(1))
		val |= BIT(3);

	mt76_wr(dev, MT_BBP(AGC, 0), val);

	mb();
	val = mt76_rr(dev, MT_BBP(AGC, 0));
}