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
struct wlandevice {int /*<<< orphan*/  netdev; int /*<<< orphan*/  bssid; } ;
struct cfg80211_roam_info {int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cfg80211_roamed (int /*<<< orphan*/ ,struct cfg80211_roam_info*,int /*<<< orphan*/ ) ; 

void prism2_roamed(struct wlandevice *wlandev)
{
	struct cfg80211_roam_info roam_info = {
		.bssid = wlandev->bssid,
	};

	cfg80211_roamed(wlandev->netdev, &roam_info, GFP_KERNEL);
}