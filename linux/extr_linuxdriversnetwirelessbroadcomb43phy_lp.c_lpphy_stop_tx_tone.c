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
struct TYPE_2__ {struct b43_phy_lp* lp; } ;
struct b43_wldev {TYPE_1__ phy; } ;
struct b43_phy_lp {scalar_t__ tx_tone_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_LPPHY_A_PHY_CTL_ADDR ; 
 int /*<<< orphan*/  B43_LPPHY_SMPL_PLAY_COUNT ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void lpphy_stop_tx_tone(struct b43_wldev *dev)
{
	struct b43_phy_lp *lpphy = dev->phy.lp;
	int i;

	lpphy->tx_tone_freq = 0;

	b43_phy_mask(dev, B43_LPPHY_SMPL_PLAY_COUNT, 0xF000);
	for (i = 0; i < 31; i++) {
		if (!(b43_phy_read(dev, B43_LPPHY_A_PHY_CTL_ADDR) & 0x1))
			break;
		udelay(100);
	}
}