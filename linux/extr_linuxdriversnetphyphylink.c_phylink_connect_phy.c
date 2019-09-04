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
struct TYPE_2__ {scalar_t__ interface; } ;
struct phylink {scalar_t__ link_interface; TYPE_1__ link_config; } ;
struct phy_device {scalar_t__ interface; } ;

/* Variables and functions */
 scalar_t__ PHY_INTERFACE_MODE_NA ; 
 int __phylink_connect_phy (struct phylink*,struct phy_device*,scalar_t__) ; 

int phylink_connect_phy(struct phylink *pl, struct phy_device *phy)
{
	/* Use PHY device/driver interface */
	if (pl->link_interface == PHY_INTERFACE_MODE_NA) {
		pl->link_interface = phy->interface;
		pl->link_config.interface = pl->link_interface;
	}

	return __phylink_connect_phy(pl, phy, pl->link_interface);
}