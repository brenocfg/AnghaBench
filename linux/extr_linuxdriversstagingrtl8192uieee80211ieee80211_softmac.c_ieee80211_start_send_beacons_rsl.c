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
struct ieee80211_device {int softmac_features; int /*<<< orphan*/  basic_rate; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* start_send_beacons ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int IEEE_SOFTMAC_BEACONS ; 
 int /*<<< orphan*/  ieee80211_beacons_start (struct ieee80211_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ieee80211_start_send_beacons(struct ieee80211_device *ieee)
{
	if (ieee->start_send_beacons)
		ieee->start_send_beacons(ieee->dev, ieee->basic_rate);
	if (ieee->softmac_features & IEEE_SOFTMAC_BEACONS)
		ieee80211_beacons_start(ieee);
}