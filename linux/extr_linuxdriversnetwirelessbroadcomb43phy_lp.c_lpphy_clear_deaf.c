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
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_1__ phy; } ;
struct b43_phy_lp {int crs_usr_disable; int crs_sys_disable; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_LPPHY_CRSGAIN_CTL ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void lpphy_clear_deaf(struct b43_wldev *dev, bool user)
{
	struct b43_phy_lp *lpphy = dev->phy.lp;

	if (user)
		lpphy->crs_usr_disable = false;
	else
		lpphy->crs_sys_disable = false;

	if (!lpphy->crs_usr_disable && !lpphy->crs_sys_disable) {
		if (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
			b43_phy_maskset(dev, B43_LPPHY_CRSGAIN_CTL,
					0xFF1F, 0x60);
		else
			b43_phy_maskset(dev, B43_LPPHY_CRSGAIN_CTL,
					0xFF1F, 0x20);
	}
}