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
struct phy_device {int /*<<< orphan*/  (* phy_link_change ) (struct phy_device*,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  phy_led_trigger_change_speed (struct phy_device*) ; 
 int /*<<< orphan*/  stub1 (struct phy_device*,int,int) ; 

__attribute__((used)) static void phy_link_down(struct phy_device *phydev, bool do_carrier)
{
	phydev->phy_link_change(phydev, false, do_carrier);
	phy_led_trigger_change_speed(phydev);
}