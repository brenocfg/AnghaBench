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
typedef  int u16 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_PHY_HT_TABLE_ADDR ; 
 int /*<<< orphan*/  B43_PHY_HT_TABLE_DATAHI ; 
 int /*<<< orphan*/  B43_PHY_HT_TABLE_DATALO ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u16 b43_phy_ht_load_samples(struct b43_wldev *dev)
{
	int i;
	u16 len = 20 << 3;

	b43_phy_write(dev, B43_PHY_HT_TABLE_ADDR, 0x4400);

	for (i = 0; i < len; i++) {
		b43_phy_write(dev, B43_PHY_HT_TABLE_DATAHI, 0);
		b43_phy_write(dev, B43_PHY_HT_TABLE_DATALO, 0);
	}

	return len;
}