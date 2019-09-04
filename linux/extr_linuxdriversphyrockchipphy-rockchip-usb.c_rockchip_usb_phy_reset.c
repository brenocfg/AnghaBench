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
struct rockchip_usb_phy {scalar_t__ reset; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 struct rockchip_usb_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  reset_control_assert (scalar_t__) ; 
 int /*<<< orphan*/  reset_control_deassert (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int rockchip_usb_phy_reset(struct phy *_phy)
{
	struct rockchip_usb_phy *phy = phy_get_drvdata(_phy);

	if (phy->reset) {
		reset_control_assert(phy->reset);
		udelay(10);
		reset_control_deassert(phy->reset);
	}

	return 0;
}