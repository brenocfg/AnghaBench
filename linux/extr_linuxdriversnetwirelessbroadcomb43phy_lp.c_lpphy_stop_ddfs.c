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
 int /*<<< orphan*/  B43_LPPHY_LP_PHY_CTL ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lpphy_stop_ddfs(struct b43_wldev *dev)
{
	b43_phy_mask(dev, B43_LPPHY_AFE_DDFS, 0xFFFD);
	b43_phy_mask(dev, B43_LPPHY_LP_PHY_CTL, 0xFFDF);
}