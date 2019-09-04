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
struct mt76x2_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_MAC_CSR0 ; 
 int mt76_rr (struct mt76x2_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static inline bool mt76x2_wait_for_mac(struct mt76x2_dev *dev)
{
	int i;

	for (i = 0; i < 500; i++) {
		switch (mt76_rr(dev, MT_MAC_CSR0)) {
		case 0:
		case ~0:
			break;
		default:
			return true;
		}
		usleep_range(5000, 10000);
	}
	return false;
}