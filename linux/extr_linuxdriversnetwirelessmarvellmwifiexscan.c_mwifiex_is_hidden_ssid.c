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
struct cfg80211_ssid {int ssid_len; scalar_t__* ssid; } ;

/* Variables and functions */

__attribute__((used)) static bool mwifiex_is_hidden_ssid(struct cfg80211_ssid *ssid)
{
	int idx;

	for (idx = 0; idx < ssid->ssid_len; idx++) {
		if (ssid->ssid[idx])
			return false;
	}

	return true;
}