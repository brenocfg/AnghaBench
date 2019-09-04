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
typedef  int u16 ;
struct TYPE_2__ {int rev; struct b43_phy_lp* lp; } ;
struct b43_wldev {TYPE_1__ phy; } ;
struct b43_phy_lp {scalar_t__ rc_cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  B2063_TX_BB_SP3 ; 
 int /*<<< orphan*/  B43_LPPHY_LP_PHY_CTL ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lpphy_set_rc_cap (struct b43_wldev*) ; 

__attribute__((used)) static void lpphy_set_analog_filter(struct b43_wldev *dev, int channel)
{
	struct b43_phy_lp *lpphy = dev->phy.lp;
	u16 tmp = (channel == 14); //SPEC FIXME check japanwidefilter!

	if (dev->phy.rev < 2) { //SPEC FIXME Isn't this rev0/1-specific?
		b43_phy_maskset(dev, B43_LPPHY_LP_PHY_CTL, 0xFCFF, tmp << 9);
		if ((dev->phy.rev == 1) && (lpphy->rc_cap))
			lpphy_set_rc_cap(dev);
	} else {
		b43_radio_write(dev, B2063_TX_BB_SP3, 0x3F);
	}
}