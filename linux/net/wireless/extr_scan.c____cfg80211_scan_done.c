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
typedef  int /*<<< orphan*/  wrqu ;
typedef  union iwreq_data {int dummy; } iwreq_data ;
struct wireless_dev {scalar_t__ netdev; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  aborted; } ;
struct cfg80211_scan_request {int flags; TYPE_1__ info; int /*<<< orphan*/  scan_start; struct wireless_dev* wdev; } ;
struct cfg80211_registered_device {struct sk_buff* scan_msg; struct cfg80211_scan_request* scan_req; int /*<<< orphan*/  bss_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int NL80211_SCAN_FLAG_FLUSH ; 
 int /*<<< orphan*/  SIOCGIWSCAN ; 
 int /*<<< orphan*/  __cfg80211_bss_expire (struct cfg80211_registered_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_sme_scan_done (scalar_t__) ; 
 int /*<<< orphan*/  dev_put (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct cfg80211_scan_request*) ; 
 int /*<<< orphan*/  memset (union iwreq_data*,int /*<<< orphan*/ ,int) ; 
 struct sk_buff* nl80211_build_scan_msg (struct cfg80211_registered_device*,struct wireless_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl80211_send_scan_msg (struct cfg80211_registered_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wireless_send_event (scalar_t__,int /*<<< orphan*/ ,union iwreq_data*,int /*<<< orphan*/ *) ; 

void ___cfg80211_scan_done(struct cfg80211_registered_device *rdev,
			   bool send_message)
{
	struct cfg80211_scan_request *request;
	struct wireless_dev *wdev;
	struct sk_buff *msg;
#ifdef CONFIG_CFG80211_WEXT
	union iwreq_data wrqu;
#endif

	ASSERT_RTNL();

	if (rdev->scan_msg) {
		nl80211_send_scan_msg(rdev, rdev->scan_msg);
		rdev->scan_msg = NULL;
		return;
	}

	request = rdev->scan_req;
	if (!request)
		return;

	wdev = request->wdev;

	/*
	 * This must be before sending the other events!
	 * Otherwise, wpa_supplicant gets completely confused with
	 * wext events.
	 */
	if (wdev->netdev)
		cfg80211_sme_scan_done(wdev->netdev);

	if (!request->info.aborted &&
	    request->flags & NL80211_SCAN_FLAG_FLUSH) {
		/* flush entries from previous scans */
		spin_lock_bh(&rdev->bss_lock);
		__cfg80211_bss_expire(rdev, request->scan_start);
		spin_unlock_bh(&rdev->bss_lock);
	}

	msg = nl80211_build_scan_msg(rdev, wdev, request->info.aborted);

#ifdef CONFIG_CFG80211_WEXT
	if (wdev->netdev && !request->info.aborted) {
		memset(&wrqu, 0, sizeof(wrqu));

		wireless_send_event(wdev->netdev, SIOCGIWSCAN, &wrqu, NULL);
	}
#endif

	if (wdev->netdev)
		dev_put(wdev->netdev);

	rdev->scan_req = NULL;
	kfree(request);

	if (!send_message)
		rdev->scan_msg = msg;
	else
		nl80211_send_scan_msg(rdev, msg);
}