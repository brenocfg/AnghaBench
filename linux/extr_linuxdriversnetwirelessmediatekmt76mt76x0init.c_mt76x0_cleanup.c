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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct mt76x0_dev {TYPE_1__ mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT76_STATE_INITIALIZED ; 
 int /*<<< orphan*/  mt76x0_dma_cleanup (struct mt76x0_dev*) ; 
 int /*<<< orphan*/  mt76x0_mcu_cmd_deinit (struct mt76x0_dev*) ; 
 int /*<<< orphan*/  mt76x0_stop_hardware (struct mt76x0_dev*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mt76x0_cleanup(struct mt76x0_dev *dev)
{
	if (!test_and_clear_bit(MT76_STATE_INITIALIZED, &dev->mt76.state))
		return;

	mt76x0_stop_hardware(dev);
	mt76x0_dma_cleanup(dev);
	mt76x0_mcu_cmd_deinit(dev);
}