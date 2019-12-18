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
struct wireless_dev {struct wiphy* wiphy; } ;
struct wiphy {int dummy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct cfg80211_bss {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bss_from_pub (struct cfg80211_bss*) ; 
 int /*<<< orphan*/  cfg80211_put_bss (struct wiphy*,struct cfg80211_bss*) ; 
 int /*<<< orphan*/  cfg80211_sme_abandon_assoc (struct wireless_dev*) ; 
 int /*<<< orphan*/  cfg80211_unhold_bss (int /*<<< orphan*/ ) ; 

void cfg80211_abandon_assoc(struct net_device *dev, struct cfg80211_bss *bss)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct wiphy *wiphy = wdev->wiphy;

	cfg80211_sme_abandon_assoc(wdev);

	cfg80211_unhold_bss(bss_from_pub(bss));
	cfg80211_put_bss(wiphy, bss);
}