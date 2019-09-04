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
typedef  int /*<<< orphan*/  u32 ;
struct mt7601u_dev {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MT7601U_STATE_REMOVED ; 
 int /*<<< orphan*/  MT_MAC_CSR0 ; 
 int /*<<< orphan*/  mt7601u_rr (struct mt7601u_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

int mt7601u_wait_asic_ready(struct mt7601u_dev *dev)
{
	int i = 100;
	u32 val;

	do {
		if (test_bit(MT7601U_STATE_REMOVED, &dev->state))
			return -EIO;

		val = mt7601u_rr(dev, MT_MAC_CSR0);
		if (val && ~val)
			return 0;

		udelay(10);
	} while (i--);

	return -EIO;
}