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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ low_gain; int false_cca; scalar_t__ agc_gain_adjust; } ;
struct mt76x2_dev {TYPE_1__ cal; } ;

/* Variables and functions */
 int FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_RX_STAT_1 ; 
 int /*<<< orphan*/  MT_RX_STAT_1_CCA_ERRORS ; 
 int /*<<< orphan*/  mt76_rr (struct mt76x2_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x2_phy_set_gain_val (struct mt76x2_dev*) ; 

__attribute__((used)) static void
mt76x2_phy_adjust_vga_gain(struct mt76x2_dev *dev)
{
	u32 false_cca;
	u8 limit = dev->cal.low_gain > 0 ? 16 : 4;

	false_cca = FIELD_GET(MT_RX_STAT_1_CCA_ERRORS, mt76_rr(dev, MT_RX_STAT_1));
	dev->cal.false_cca = false_cca;
	if (false_cca > 800 && dev->cal.agc_gain_adjust < limit)
		dev->cal.agc_gain_adjust += 2;
	else if ((false_cca < 10 && dev->cal.agc_gain_adjust > 0) ||
		 (dev->cal.agc_gain_adjust >= limit && false_cca < 500))
		dev->cal.agc_gain_adjust -= 2;
	else
		return;

	mt76x2_phy_set_gain_val(dev);
}