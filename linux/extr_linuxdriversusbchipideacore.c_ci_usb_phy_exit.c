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
struct ci_hdrc {int /*<<< orphan*/  usb_phy; scalar_t__ phy; TYPE_1__* platdata; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int CI_HDRC_OVERRIDE_PHY_CONTROL ; 
 int /*<<< orphan*/  phy_exit (scalar_t__) ; 
 int /*<<< orphan*/  phy_power_off (scalar_t__) ; 
 int /*<<< orphan*/  usb_phy_shutdown (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ci_usb_phy_exit(struct ci_hdrc *ci)
{
	if (ci->platdata->flags & CI_HDRC_OVERRIDE_PHY_CONTROL)
		return;

	if (ci->phy) {
		phy_power_off(ci->phy);
		phy_exit(ci->phy);
	} else {
		usb_phy_shutdown(ci->usb_phy);
	}
}