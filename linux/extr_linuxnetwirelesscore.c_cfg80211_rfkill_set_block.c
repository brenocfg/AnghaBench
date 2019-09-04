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
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfg80211_shutdown_all_interfaces (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int cfg80211_rfkill_set_block(void *data, bool blocked)
{
	struct cfg80211_registered_device *rdev = data;

	if (!blocked)
		return 0;

	rtnl_lock();
	cfg80211_shutdown_all_interfaces(&rdev->wiphy);
	rtnl_unlock();

	return 0;
}