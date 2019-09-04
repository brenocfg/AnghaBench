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
struct wireless_dev {int iftype; } ;
struct brcmf_if {TYPE_1__* vif; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;
struct TYPE_2__ {struct wireless_dev wdev; } ;

/* Variables and functions */

enum nl80211_iftype brcmf_cfg80211_get_iftype(struct brcmf_if *ifp)
{
	struct wireless_dev *wdev = &ifp->vif->wdev;

	return wdev->iftype;
}