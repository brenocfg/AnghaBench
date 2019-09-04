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
struct usb_phy {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ULPI_OTG_CTRL ; 
 unsigned int ULPI_OTG_CTRL_DM_PULLDOWN ; 
 unsigned int ULPI_OTG_CTRL_DP_PULLDOWN ; 
 unsigned int ULPI_OTG_CTRL_EXTVBUSIND ; 
 unsigned int ULPI_OTG_CTRL_ID_PULLUP ; 
 int ULPI_OTG_DM_PULLDOWN_DIS ; 
 int ULPI_OTG_DP_PULLDOWN_DIS ; 
 int ULPI_OTG_EXTVBUSIND ; 
 int ULPI_OTG_ID_PULLUP ; 
 int usb_phy_io_write (struct usb_phy*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ulpi_set_otg_flags(struct usb_phy *phy)
{
	unsigned int flags = ULPI_OTG_CTRL_DP_PULLDOWN |
			     ULPI_OTG_CTRL_DM_PULLDOWN;

	if (phy->flags & ULPI_OTG_ID_PULLUP)
		flags |= ULPI_OTG_CTRL_ID_PULLUP;

	/*
	 * ULPI Specification rev.1.1 default
	 * for Dp/DmPulldown is enabled.
	 */
	if (phy->flags & ULPI_OTG_DP_PULLDOWN_DIS)
		flags &= ~ULPI_OTG_CTRL_DP_PULLDOWN;

	if (phy->flags & ULPI_OTG_DM_PULLDOWN_DIS)
		flags &= ~ULPI_OTG_CTRL_DM_PULLDOWN;

	if (phy->flags & ULPI_OTG_EXTVBUSIND)
		flags |= ULPI_OTG_CTRL_EXTVBUSIND;

	return usb_phy_io_write(phy, flags, ULPI_OTG_CTRL);
}