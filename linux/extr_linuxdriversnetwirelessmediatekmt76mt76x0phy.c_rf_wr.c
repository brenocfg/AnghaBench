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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct mt76x0_dev {TYPE_1__ mt76; } ;
struct mt76_reg_pair {int /*<<< orphan*/  value; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT76_STATE_MCU_RUNNING ; 
 int /*<<< orphan*/  MT_MCU_MEMMAP_RF ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int mt76x0_rf_csr_wr (struct mt76x0_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mt76x0_write_reg_pairs (struct mt76x0_dev*,int /*<<< orphan*/ ,struct mt76_reg_pair*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
rf_wr(struct mt76x0_dev *dev, u32 offset, u8 val)
{
	if (test_bit(MT76_STATE_MCU_RUNNING, &dev->mt76.state)) {
		struct mt76_reg_pair pair = {
			.reg = offset,
			.value = val,
		};

		return mt76x0_write_reg_pairs(dev, MT_MCU_MEMMAP_RF, &pair, 1);
	} else {
		WARN_ON_ONCE(1);
		return mt76x0_rf_csr_wr(dev, offset, val);
	}
}