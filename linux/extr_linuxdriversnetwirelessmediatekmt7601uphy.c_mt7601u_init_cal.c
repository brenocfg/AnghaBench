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
typedef  int /*<<< orphan*/  u32 ;
struct mt7601u_dev {int raw_temp; int curr_temp; int dpd_temp; TYPE_1__* ee; } ;
struct TYPE_2__ {int ref_temp; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCU_CAL_DPD ; 
 int /*<<< orphan*/  MCU_CAL_LOFT ; 
 int /*<<< orphan*/  MCU_CAL_R ; 
 int /*<<< orphan*/  MCU_CAL_RXIQ ; 
 int /*<<< orphan*/  MCU_CAL_TXDCOC ; 
 int /*<<< orphan*/  MCU_CAL_TXIQ ; 
 int MT_EE_TEMPERATURE_SLOPE ; 
 int /*<<< orphan*/  MT_MAC_SYS_CTRL ; 
 int /*<<< orphan*/  msleep (int) ; 
 int mt7601u_mcu_calibrate (struct mt7601u_dev*,int /*<<< orphan*/ ,int) ; 
 int mt7601u_read_bootup_temp (struct mt7601u_dev*) ; 
 int mt7601u_rf_rr (struct mt7601u_dev*,int /*<<< orphan*/ ,int) ; 
 int mt7601u_rf_wr (struct mt7601u_dev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mt7601u_rr (struct mt7601u_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7601u_rxdc_cal (struct mt7601u_dev*) ; 
 int mt7601u_set_bw_filter (struct mt7601u_dev*,int) ; 
 int /*<<< orphan*/  mt7601u_temp_comp (struct mt7601u_dev*,int) ; 
 int /*<<< orphan*/  mt7601u_tssi_dc_gain_cal (struct mt7601u_dev*) ; 
 int /*<<< orphan*/  mt7601u_wr (struct mt7601u_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt7601u_init_cal(struct mt7601u_dev *dev)
{
	u32 mac_ctrl;
	int ret;

	dev->raw_temp = mt7601u_read_bootup_temp(dev);
	dev->curr_temp = (dev->raw_temp - dev->ee->ref_temp) *
		MT_EE_TEMPERATURE_SLOPE;
	dev->dpd_temp = dev->curr_temp;

	mac_ctrl = mt7601u_rr(dev, MT_MAC_SYS_CTRL);

	ret = mt7601u_mcu_calibrate(dev, MCU_CAL_R, 0);
	if (ret)
		return ret;

	ret = mt7601u_rf_rr(dev, 0, 4);
	if (ret < 0)
		return ret;
	ret |= 0x80;
	ret = mt7601u_rf_wr(dev, 0, 4, ret);
	if (ret)
		return ret;
	msleep(2);

	ret = mt7601u_mcu_calibrate(dev, MCU_CAL_TXDCOC, 0);
	if (ret)
		return ret;

	mt7601u_rxdc_cal(dev);

	ret = mt7601u_set_bw_filter(dev, true);
	if (ret)
		return ret;
	ret = mt7601u_mcu_calibrate(dev, MCU_CAL_LOFT, 0);
	if (ret)
		return ret;
	ret = mt7601u_mcu_calibrate(dev, MCU_CAL_TXIQ, 0);
	if (ret)
		return ret;
	ret = mt7601u_mcu_calibrate(dev, MCU_CAL_RXIQ, 0);
	if (ret)
		return ret;
	ret = mt7601u_mcu_calibrate(dev, MCU_CAL_DPD, dev->dpd_temp);
	if (ret)
		return ret;

	mt7601u_rxdc_cal(dev);

	mt7601u_tssi_dc_gain_cal(dev);

	mt7601u_wr(dev, MT_MAC_SYS_CTRL, mac_ctrl);

	mt7601u_temp_comp(dev, true);

	return 0;
}