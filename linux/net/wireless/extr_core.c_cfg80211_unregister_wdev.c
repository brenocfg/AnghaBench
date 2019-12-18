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
struct wireless_dev {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cfg80211_unregister_wdev (struct wireless_dev*,int) ; 

void cfg80211_unregister_wdev(struct wireless_dev *wdev)
{
	if (WARN_ON(wdev->netdev))
		return;

	__cfg80211_unregister_wdev(wdev, true);
}