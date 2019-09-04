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
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_LPPHY_RF_OVERRIDE_0 ; 
 int /*<<< orphan*/  B43_LPPHY_RF_OVERRIDE_2 ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lpphy_clear_deaf (struct b43_wldev*,int) ; 

__attribute__((used)) static void lpphy_restore_crs(struct b43_wldev *dev, bool user)
{
	lpphy_clear_deaf(dev, user);
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_0, 0xFF80);
	b43_phy_mask(dev, B43_LPPHY_RF_OVERRIDE_2, 0xFC00);
}