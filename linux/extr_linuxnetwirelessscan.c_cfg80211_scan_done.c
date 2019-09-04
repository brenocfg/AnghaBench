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
struct cfg80211_scan_info {int dummy; } ;
struct cfg80211_scan_request {int notified; int /*<<< orphan*/  wiphy; struct cfg80211_scan_info info; } ;
struct TYPE_2__ {int /*<<< orphan*/  scan_done_wk; struct cfg80211_scan_request* scan_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cfg80211_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_cfg80211_scan_done (struct cfg80211_scan_request*,struct cfg80211_scan_info*) ; 
 TYPE_1__* wiphy_to_rdev (int /*<<< orphan*/ ) ; 

void cfg80211_scan_done(struct cfg80211_scan_request *request,
			struct cfg80211_scan_info *info)
{
	trace_cfg80211_scan_done(request, info);
	WARN_ON(request != wiphy_to_rdev(request->wiphy)->scan_req);

	request->info = *info;
	request->notified = true;
	queue_work(cfg80211_wq, &wiphy_to_rdev(request->wiphy)->scan_done_wk);
}