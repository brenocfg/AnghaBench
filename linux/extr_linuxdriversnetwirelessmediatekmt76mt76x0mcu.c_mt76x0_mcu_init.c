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
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;
struct mt76x0_dev {TYPE_2__ mt76; TYPE_1__ mcu; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT76_STATE_MCU_RUNNING ; 
 int mt76x0_load_firmware (struct mt76x0_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mt76x0_mcu_init(struct mt76x0_dev *dev)
{
	int ret;

	mutex_init(&dev->mcu.mutex);

	ret = mt76x0_load_firmware(dev);
	if (ret)
		return ret;

	set_bit(MT76_STATE_MCU_RUNNING, &dev->mt76.state);

	return 0;
}