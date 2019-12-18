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
struct wiphy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_WDEV_TO_SUB_IF (struct wireless_dev*) ; 
 int /*<<< orphan*/  ieee80211_if_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ieee80211_del_iface(struct wiphy *wiphy, struct wireless_dev *wdev)
{
	ieee80211_if_remove(IEEE80211_WDEV_TO_SUB_IF(wdev));

	return 0;
}