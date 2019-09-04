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
 int /*<<< orphan*/  B43_LPPHY_AFE_DDFS ; 
 int /*<<< orphan*/  B43_LPPHY_AFE_DDFS_INCR_INIT ; 
 int /*<<< orphan*/  B43_LPPHY_AFE_DDFS_POINTER_INIT ; 
 int /*<<< orphan*/  B43_LPPHY_LP_PHY_CTL ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lpphy_stop_ddfs (struct b43_wldev*) ; 

__attribute__((used)) static void lpphy_run_ddfs(struct b43_wldev *dev, int i_on, int q_on,
			   int incr1, int incr2, int scale_idx)
{
	lpphy_stop_ddfs(dev);
	b43_phy_mask(dev, B43_LPPHY_AFE_DDFS_POINTER_INIT, 0xFF80);
	b43_phy_mask(dev, B43_LPPHY_AFE_DDFS_POINTER_INIT, 0x80FF);
	b43_phy_maskset(dev, B43_LPPHY_AFE_DDFS_INCR_INIT, 0xFF80, incr1);
	b43_phy_maskset(dev, B43_LPPHY_AFE_DDFS_INCR_INIT, 0x80FF, incr2 << 8);
	b43_phy_maskset(dev, B43_LPPHY_AFE_DDFS, 0xFFF7, i_on << 3);
	b43_phy_maskset(dev, B43_LPPHY_AFE_DDFS, 0xFFEF, q_on << 4);
	b43_phy_maskset(dev, B43_LPPHY_AFE_DDFS, 0xFF9F, scale_idx << 5);
	b43_phy_mask(dev, B43_LPPHY_AFE_DDFS, 0xFFFB);
	b43_phy_set(dev, B43_LPPHY_AFE_DDFS, 0x2);
	b43_phy_set(dev, B43_LPPHY_LP_PHY_CTL, 0x20);
}