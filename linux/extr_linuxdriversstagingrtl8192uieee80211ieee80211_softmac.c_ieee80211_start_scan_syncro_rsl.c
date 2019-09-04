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
struct ieee80211_device {int softmac_features; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* scan_syncro ) (int /*<<< orphan*/ ) ;scalar_t__ sync_scan_hurryup; } ;

/* Variables and functions */
 int IEEE_SOFTMAC_SCAN ; 
 scalar_t__ IS_COUNTRY_IE_VALID (struct ieee80211_device*) ; 
 scalar_t__ IS_DOT11D_ENABLE (struct ieee80211_device*) ; 
 int /*<<< orphan*/  RESET_CIE_WATCHDOG (struct ieee80211_device*) ; 
 int /*<<< orphan*/  ieee80211_softmac_scan_syncro (struct ieee80211_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void ieee80211_start_scan_syncro(struct ieee80211_device *ieee)
{
	if (IS_DOT11D_ENABLE(ieee)) {
		if (IS_COUNTRY_IE_VALID(ieee))
			RESET_CIE_WATCHDOG(ieee);
	}
	ieee->sync_scan_hurryup = 0;
	if (ieee->softmac_features & IEEE_SOFTMAC_SCAN)
		ieee80211_softmac_scan_syncro(ieee);
	else
		ieee->scan_syncro(ieee->dev);
}