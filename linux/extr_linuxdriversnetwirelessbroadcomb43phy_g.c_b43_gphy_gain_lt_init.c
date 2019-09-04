#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u16 ;
struct b43_phy {int radio_rev; struct b43_phy_g* g; } ;
struct b43_wldev {struct b43_phy phy; } ;
struct TYPE_8__ {size_t len; TYPE_3__* list; } ;
struct TYPE_6__ {size_t len; TYPE_1__* list; } ;
struct b43_txpower_lo_control {TYPE_4__ rfatt_list; TYPE_2__ bbatt_list; } ;
struct b43_phy_g {struct b43_txpower_lo_control* lo_control; } ;
struct TYPE_7__ {int att; } ;
struct TYPE_5__ {int att; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int,int) ; 

__attribute__((used)) static void b43_gphy_gain_lt_init(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_g *gphy = phy->g;
	struct b43_txpower_lo_control *lo = gphy->lo_control;
	u16 nr_written = 0;
	u16 tmp;
	u8 rf, bb;

	for (rf = 0; rf < lo->rfatt_list.len; rf++) {
		for (bb = 0; bb < lo->bbatt_list.len; bb++) {
			if (nr_written >= 0x40)
				return;
			tmp = lo->bbatt_list.list[bb].att;
			tmp <<= 8;
			if (phy->radio_rev == 8)
				tmp |= 0x50;
			else
				tmp |= 0x40;
			tmp |= lo->rfatt_list.list[rf].att;
			b43_phy_write(dev, 0x3C0 + nr_written, tmp);
			nr_written++;
		}
	}
}