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
typedef  int u8 ;
struct mt76x0_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_RF (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int rf_rr (struct mt76x0_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rf_wr (struct mt76x0_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mt76x0_vco_cal(struct mt76x0_dev *dev, u8 channel)
{
	u8 val;

	val = rf_rr(dev, MT_RF(0, 4));
	if ((val & 0x70) != 0x30)
		return;

	/*
	 * Calibration Mode - Open loop, closed loop, and amplitude:
	 * B0.R06.[0]: 1
	 * B0.R06.[3:1] bp_close_code: 100
	 * B0.R05.[7:0] bp_open_code: 0x0
	 * B0.R04.[2:0] cal_bits: 000
	 * B0.R03.[2:0] startup_time: 011
	 * B0.R03.[6:4] settle_time:
	 *  80MHz channel: 110
	 *  40MHz channel: 101
	 *  20MHz channel: 100
	 */
	val = rf_rr(dev, MT_RF(0, 6));
	val &= ~0xf;
	val |= 0x09;
	rf_wr(dev, MT_RF(0, 6), val);

	val = rf_rr(dev, MT_RF(0, 5));
	if (val != 0)
		rf_wr(dev, MT_RF(0, 5), 0x0);

	val = rf_rr(dev, MT_RF(0, 4));
	val &= ~0x07;
	rf_wr(dev, MT_RF(0, 4), val);

	val = rf_rr(dev, MT_RF(0, 3));
	val &= ~0x77;
	if (channel == 1 || channel == 7 || channel == 9 || channel >= 13) {
		val |= 0x63;
	} else if (channel == 3 || channel == 4 || channel == 10) {
		val |= 0x53;
	} else if (channel == 2 || channel == 5 || channel == 6 ||
		   channel == 8 || channel == 11 || channel == 12) {
		val |= 0x43;
	} else {
		WARN(1, "Unknown channel %u\n", channel);
		return;
	}
	rf_wr(dev, MT_RF(0, 3), val);

	/* TODO replace by mt76x0_rf_set(dev, MT_RF(0, 4), BIT(7)); */
	val = rf_rr(dev, MT_RF(0, 4));
	val = ((val & ~(0x80)) | 0x80);
	rf_wr(dev, MT_RF(0, 4), val);

	msleep(2);
}