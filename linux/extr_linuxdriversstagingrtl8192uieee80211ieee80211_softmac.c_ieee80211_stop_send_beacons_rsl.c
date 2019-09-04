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
struct ieee80211_device {int softmac_features; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* stop_send_beacons ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int IEEE_SOFTMAC_BEACONS ; 
 int /*<<< orphan*/  ieee80211_beacons_stop (struct ieee80211_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void ieee80211_stop_send_beacons(struct ieee80211_device *ieee)
{
	if (ieee->stop_send_beacons)
		ieee->stop_send_beacons(ieee->dev);
	if (ieee->softmac_features & IEEE_SOFTMAC_BEACONS)
		ieee80211_beacons_stop(ieee);
}