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
struct cfg80211_sched_scan_request {int /*<<< orphan*/  reqid; int /*<<< orphan*/  dev; } ;
struct cfg80211_registered_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  NL80211_CMD_SCHED_SCAN_STOPPED ; 
 int /*<<< orphan*/  cfg80211_del_sched_scan_req (struct cfg80211_registered_device*,struct cfg80211_sched_scan_request*) ; 
 int /*<<< orphan*/  nl80211_send_sched_scan (struct cfg80211_sched_scan_request*,int /*<<< orphan*/ ) ; 
 int rdev_sched_scan_stop (struct cfg80211_registered_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cfg80211_stop_sched_scan_req(struct cfg80211_registered_device *rdev,
				 struct cfg80211_sched_scan_request *req,
				 bool driver_initiated)
{
	ASSERT_RTNL();

	if (!driver_initiated) {
		int err = rdev_sched_scan_stop(rdev, req->dev, req->reqid);
		if (err)
			return err;
	}

	nl80211_send_sched_scan(req, NL80211_CMD_SCHED_SCAN_STOPPED);

	cfg80211_del_sched_scan_req(rdev, req);

	return 0;
}