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
struct mt76x0_dev {int chainmask; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  MT_BBP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TXBE ; 
 int /*<<< orphan*/  mt76_clear (struct mt76x0_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_set (struct mt76x0_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mt76x0_set_tx_dac(struct mt76x0_dev *dev)
{
	if (dev->chainmask & BIT(1))
		mt76_set(dev, MT_BBP(TXBE, 5), 3);
	else
		mt76_clear(dev, MT_BBP(TXBE, 5), 3);
}