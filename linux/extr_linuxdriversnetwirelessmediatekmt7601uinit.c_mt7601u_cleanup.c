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
struct mt7601u_dev {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT7601U_STATE_INITIALIZED ; 
 int /*<<< orphan*/  mt7601u_dma_cleanup (struct mt7601u_dev*) ; 
 int /*<<< orphan*/  mt7601u_mcu_cmd_deinit (struct mt7601u_dev*) ; 
 int /*<<< orphan*/  mt7601u_stop_hardware (struct mt7601u_dev*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mt7601u_cleanup(struct mt7601u_dev *dev)
{
	if (!test_and_clear_bit(MT7601U_STATE_INITIALIZED, &dev->state))
		return;

	mt7601u_stop_hardware(dev);
	mt7601u_dma_cleanup(dev);
	mt7601u_mcu_cmd_deinit(dev);
}