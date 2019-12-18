#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int wpa_versions; } ;
struct TYPE_5__ {TYPE_1__ crypto; } ;
struct TYPE_6__ {TYPE_2__ connect; } ;
struct wireless_dev {TYPE_3__ wext; } ;

/* Variables and functions */
 int EINVAL ; 
 int IW_AUTH_WPA_VERSION_DISABLED ; 
 int IW_AUTH_WPA_VERSION_WPA ; 
 int IW_AUTH_WPA_VERSION_WPA2 ; 
 int NL80211_WPA_VERSION_1 ; 
 int NL80211_WPA_VERSION_2 ; 

__attribute__((used)) static int cfg80211_set_wpa_version(struct wireless_dev *wdev, u32 wpa_versions)
{
	if (wpa_versions & ~(IW_AUTH_WPA_VERSION_WPA |
			     IW_AUTH_WPA_VERSION_WPA2|
		             IW_AUTH_WPA_VERSION_DISABLED))
		return -EINVAL;

	if ((wpa_versions & IW_AUTH_WPA_VERSION_DISABLED) &&
	    (wpa_versions & (IW_AUTH_WPA_VERSION_WPA|
			     IW_AUTH_WPA_VERSION_WPA2)))
		return -EINVAL;

	if (wpa_versions & IW_AUTH_WPA_VERSION_DISABLED)
		wdev->wext.connect.crypto.wpa_versions &=
			~(NL80211_WPA_VERSION_1|NL80211_WPA_VERSION_2);

	if (wpa_versions & IW_AUTH_WPA_VERSION_WPA)
		wdev->wext.connect.crypto.wpa_versions |=
			NL80211_WPA_VERSION_1;

	if (wpa_versions & IW_AUTH_WPA_VERSION_WPA2)
		wdev->wext.connect.crypto.wpa_versions |=
			NL80211_WPA_VERSION_2;

	return 0;
}