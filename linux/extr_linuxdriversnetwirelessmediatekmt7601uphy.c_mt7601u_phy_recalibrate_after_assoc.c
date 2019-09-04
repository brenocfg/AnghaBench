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
struct mt7601u_dev {int /*<<< orphan*/  curr_temp; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCU_CAL_DPD ; 
 int /*<<< orphan*/  mt7601u_mcu_calibrate (struct mt7601u_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7601u_rxdc_cal (struct mt7601u_dev*) ; 

void mt7601u_phy_recalibrate_after_assoc(struct mt7601u_dev *dev)
{
	mt7601u_mcu_calibrate(dev, MCU_CAL_DPD, dev->curr_temp);

	mt7601u_rxdc_cal(dev);
}