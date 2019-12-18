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
struct wireless_dev {int dummy; } ;
struct sk_buff {int dummy; } ;
struct cfg80211_registered_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NL80211_CMD_NEW_SCAN_RESULTS ; 
 int /*<<< orphan*/  NL80211_CMD_SCAN_ABORTED ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 scalar_t__ nl80211_prep_scan_msg (struct sk_buff*,struct cfg80211_registered_device*,struct wireless_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct sk_buff *nl80211_build_scan_msg(struct cfg80211_registered_device *rdev,
				       struct wireless_dev *wdev, bool aborted)
{
	struct sk_buff *msg;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg)
		return NULL;

	if (nl80211_prep_scan_msg(msg, rdev, wdev, 0, 0, 0,
				  aborted ? NL80211_CMD_SCAN_ABORTED :
					    NL80211_CMD_NEW_SCAN_RESULTS) < 0) {
		nlmsg_free(msg);
		return NULL;
	}

	return msg;
}