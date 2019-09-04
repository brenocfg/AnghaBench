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
struct twl4030_usb {int /*<<< orphan*/  dev; int /*<<< orphan*/  id_workaround_work; int /*<<< orphan*/  linkstat; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  MUSB_UNKNOWN ; 
 struct twl4030_usb* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_phy_init(struct phy *phy)
{
	struct twl4030_usb *twl = phy_get_drvdata(phy);

	pm_runtime_get_sync(twl->dev);
	twl->linkstat = MUSB_UNKNOWN;
	schedule_delayed_work(&twl->id_workaround_work, HZ);
	pm_runtime_mark_last_busy(twl->dev);
	pm_runtime_put_autosuspend(twl->dev);

	return 0;
}