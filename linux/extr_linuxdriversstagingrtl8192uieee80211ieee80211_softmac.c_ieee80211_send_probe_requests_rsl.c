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
struct ieee80211_device {int softmac_features; scalar_t__ active_scan; } ;

/* Variables and functions */
 int IEEE_SOFTMAC_PROBERQ ; 
 int /*<<< orphan*/  ieee80211_send_probe (struct ieee80211_device*) ; 

__attribute__((used)) static void ieee80211_send_probe_requests(struct ieee80211_device *ieee)
{
	if (ieee->active_scan && (ieee->softmac_features & IEEE_SOFTMAC_PROBERQ)) {
		ieee80211_send_probe(ieee);
		ieee80211_send_probe(ieee);
	}
}