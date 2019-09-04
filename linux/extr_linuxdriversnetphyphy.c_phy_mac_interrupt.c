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
struct phy_device {int /*<<< orphan*/  phy_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

void phy_mac_interrupt(struct phy_device *phydev)
{
	/* Trigger a state machine change */
	queue_work(system_power_efficient_wq, &phydev->phy_queue);
}