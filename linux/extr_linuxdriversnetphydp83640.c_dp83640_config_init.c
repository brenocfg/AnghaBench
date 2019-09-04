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
struct phy_device {struct dp83640_private* priv; } ;
struct dp83640_private {struct dp83640_clock* clock; } ;
struct dp83640_clock {int /*<<< orphan*/  extreg_lock; int /*<<< orphan*/  page; int /*<<< orphan*/  phylist; scalar_t__ chosen; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE4 ; 
 int /*<<< orphan*/  PTP_CTL ; 
 int /*<<< orphan*/  PTP_ENABLE ; 
 int /*<<< orphan*/  enable_broadcast (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  enable_status_frames (struct phy_device*,int) ; 
 int /*<<< orphan*/  ext_write (int /*<<< orphan*/ ,struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  recalibrate (struct dp83640_clock*) ; 

__attribute__((used)) static int dp83640_config_init(struct phy_device *phydev)
{
	struct dp83640_private *dp83640 = phydev->priv;
	struct dp83640_clock *clock = dp83640->clock;

	if (clock->chosen && !list_empty(&clock->phylist))
		recalibrate(clock);
	else {
		mutex_lock(&clock->extreg_lock);
		enable_broadcast(phydev, clock->page, 1);
		mutex_unlock(&clock->extreg_lock);
	}

	enable_status_frames(phydev, true);

	mutex_lock(&clock->extreg_lock);
	ext_write(0, phydev, PAGE4, PTP_CTL, PTP_ENABLE);
	mutex_unlock(&clock->extreg_lock);

	return 0;
}