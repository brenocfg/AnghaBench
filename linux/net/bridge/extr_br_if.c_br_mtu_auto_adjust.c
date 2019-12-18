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
struct net_bridge {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  BROPT_MTU_SET_BY_USER ; 
 int /*<<< orphan*/  br_mtu_min (struct net_bridge*) ; 
 scalar_t__ br_opt_get (struct net_bridge*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_opt_toggle (struct net_bridge*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_set_mtu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void br_mtu_auto_adjust(struct net_bridge *br)
{
	ASSERT_RTNL();

	/* if the bridge MTU was manually configured don't mess with it */
	if (br_opt_get(br, BROPT_MTU_SET_BY_USER))
		return;

	/* change to the minimum MTU and clear the flag which was set by
	 * the bridge ndo_change_mtu callback
	 */
	dev_set_mtu(br->dev, br_mtu_min(br));
	br_opt_toggle(br, BROPT_MTU_SET_BY_USER, false);
}