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
typedef  int u32 ;
struct mt7601u_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT7601U_STATE_REMOVED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int mt7601u_rr (struct mt7601u_dev*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

bool mt76_poll(struct mt7601u_dev *dev, u32 offset, u32 mask, u32 val,
	       int timeout)
{
	u32 cur;

	timeout /= 10;
	do {
		if (test_bit(MT7601U_STATE_REMOVED, &dev->state))
			return false;

		cur = mt7601u_rr(dev, offset) & mask;
		if (cur == val)
			return true;

		udelay(10);
	} while (timeout-- > 0);

	dev_err(dev->dev, "Error: Time out with reg %08x\n", offset);

	return false;
}