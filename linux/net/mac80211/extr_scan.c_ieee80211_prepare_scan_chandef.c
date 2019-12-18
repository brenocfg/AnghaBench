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
struct cfg80211_chan_def {int /*<<< orphan*/  width; } ;
typedef  enum nl80211_bss_scan_width { ____Placeholder_nl80211_bss_scan_width } nl80211_bss_scan_width ;

/* Variables and functions */
#define  NL80211_BSS_CHAN_WIDTH_10 129 
#define  NL80211_BSS_CHAN_WIDTH_5 128 
 int /*<<< orphan*/  NL80211_CHAN_WIDTH_10 ; 
 int /*<<< orphan*/  NL80211_CHAN_WIDTH_20_NOHT ; 
 int /*<<< orphan*/  NL80211_CHAN_WIDTH_5 ; 
 int /*<<< orphan*/  memset (struct cfg80211_chan_def*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ieee80211_prepare_scan_chandef(struct cfg80211_chan_def *chandef,
			       enum nl80211_bss_scan_width scan_width)
{
	memset(chandef, 0, sizeof(*chandef));
	switch (scan_width) {
	case NL80211_BSS_CHAN_WIDTH_5:
		chandef->width = NL80211_CHAN_WIDTH_5;
		break;
	case NL80211_BSS_CHAN_WIDTH_10:
		chandef->width = NL80211_CHAN_WIDTH_10;
		break;
	default:
		chandef->width = NL80211_CHAN_WIDTH_20_NOHT;
		break;
	}
}