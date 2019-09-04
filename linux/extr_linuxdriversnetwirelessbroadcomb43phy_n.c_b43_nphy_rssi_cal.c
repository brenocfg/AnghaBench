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
struct TYPE_2__ {int rev; } ;
struct b43_wldev {TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  N_RSSI_NB ; 
 int /*<<< orphan*/  N_RSSI_W1 ; 
 int /*<<< orphan*/  N_RSSI_W2 ; 
 int /*<<< orphan*/  b43_nphy_rev2_rssi_cal (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_nphy_rev3_rssi_cal (struct b43_wldev*) ; 

__attribute__((used)) static void b43_nphy_rssi_cal(struct b43_wldev *dev)
{
	if (dev->phy.rev >= 19) {
		/* TODO */
	} else if (dev->phy.rev >= 3) {
		b43_nphy_rev3_rssi_cal(dev);
	} else {
		b43_nphy_rev2_rssi_cal(dev, N_RSSI_NB);
		b43_nphy_rev2_rssi_cal(dev, N_RSSI_W1);
		b43_nphy_rev2_rssi_cal(dev, N_RSSI_W2);
	}
}