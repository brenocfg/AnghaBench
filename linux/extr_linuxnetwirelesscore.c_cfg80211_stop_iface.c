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
struct wireless_dev {int /*<<< orphan*/  event_lock; int /*<<< orphan*/  event_list; } ;
struct wiphy {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  event_work; } ;
struct cfg80211_event {int /*<<< orphan*/  list; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_STOPPED ; 
 int /*<<< orphan*/  cfg80211_wq ; 
 struct cfg80211_event* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_cfg80211_stop_iface (struct wiphy*,struct wireless_dev*) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (struct wiphy*) ; 

void cfg80211_stop_iface(struct wiphy *wiphy, struct wireless_dev *wdev,
			 gfp_t gfp)
{
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wiphy);
	struct cfg80211_event *ev;
	unsigned long flags;

	trace_cfg80211_stop_iface(wiphy, wdev);

	ev = kzalloc(sizeof(*ev), gfp);
	if (!ev)
		return;

	ev->type = EVENT_STOPPED;

	spin_lock_irqsave(&wdev->event_lock, flags);
	list_add_tail(&ev->list, &wdev->event_list);
	spin_unlock_irqrestore(&wdev->event_lock, flags);
	queue_work(cfg80211_wq, &rdev->event_work);
}