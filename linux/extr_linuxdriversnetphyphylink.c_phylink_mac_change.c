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
struct phylink {int mac_link_dropped; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  phylink_run_resolve (struct phylink*) ; 

void phylink_mac_change(struct phylink *pl, bool up)
{
	if (!up)
		pl->mac_link_dropped = true;
	phylink_run_resolve(pl);
	netdev_dbg(pl->netdev, "mac link %s\n", up ? "up" : "down");
}