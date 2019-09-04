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
struct mt7601u_dev {int tssi_read_trig; int /*<<< orphan*/  dev; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_TSSI_SETTING ; 
 int /*<<< orphan*/  MT7601U_STATE_MCU_RUNNING ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int mt7601u_mcu_function_select (struct mt7601u_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mt7601u_mcu_tssi_read_kick(struct mt7601u_dev *dev, int use_hvga)
{
	int ret;

	if (!test_bit(MT7601U_STATE_MCU_RUNNING, &dev->state))
		return 0;

	ret = mt7601u_mcu_function_select(dev, ATOMIC_TSSI_SETTING,
					  use_hvga);
	if (ret) {
		dev_warn(dev->dev, "Warning: MCU TSSI read kick failed\n");
		return ret;
	}

	dev->tssi_read_trig = true;

	return 0;
}