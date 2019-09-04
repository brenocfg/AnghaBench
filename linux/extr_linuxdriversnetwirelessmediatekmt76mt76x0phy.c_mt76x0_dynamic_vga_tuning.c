#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {TYPE_1__* chan; } ;
struct TYPE_6__ {TYPE_2__ chandef; } ;
struct mt76x0_dev {int avg_rssi; TYPE_3__ mt76; } ;
struct TYPE_4__ {scalar_t__ band; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGC ; 
 int /*<<< orphan*/  MT_BBP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 int mt76_rr (struct mt76x0_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x0_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mt76x0_dynamic_vga_tuning(struct mt76x0_dev *dev)
{
	u32 val, init_vga;

	init_vga = (dev->mt76.chandef.chan->band == NL80211_BAND_5GHZ) ? 0x54 : 0x4E;
	if (dev->avg_rssi > -60)
		init_vga -= 0x20;
	else if (dev->avg_rssi > -70)
		init_vga -= 0x10;

	val = mt76_rr(dev, MT_BBP(AGC, 8));
	val &= 0xFFFF80FF;
	val |= init_vga << 8;
	mt76_wr(dev, MT_BBP(AGC,8), val);
}