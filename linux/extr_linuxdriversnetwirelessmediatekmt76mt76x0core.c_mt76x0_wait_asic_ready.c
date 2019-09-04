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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct mt76x0_dev {TYPE_1__ mt76; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MT76_REMOVED ; 
 int /*<<< orphan*/  MT_MAC_CSR0 ; 
 int /*<<< orphan*/  mt76_rr (struct mt76x0_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

int mt76x0_wait_asic_ready(struct mt76x0_dev *dev)
{
	int i = 100;
	u32 val;

	do {
		if (test_bit(MT76_REMOVED, &dev->mt76.state))
			return -EIO;

		val = mt76_rr(dev, MT_MAC_CSR0);
		if (val && ~val)
			return 0;

		udelay(10);
	} while (i--);

	return -EIO;
}