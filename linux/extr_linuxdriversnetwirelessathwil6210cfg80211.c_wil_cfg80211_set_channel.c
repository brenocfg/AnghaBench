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
struct wiphy {int dummy; } ;
struct cfg80211_chan_def {int dummy; } ;
struct wil6210_priv {struct cfg80211_chan_def monitor_chandef; } ;

/* Variables and functions */
 struct wil6210_priv* wiphy_to_wil (struct wiphy*) ; 

__attribute__((used)) static int wil_cfg80211_set_channel(struct wiphy *wiphy,
				    struct cfg80211_chan_def *chandef)
{
	struct wil6210_priv *wil = wiphy_to_wil(wiphy);

	wil->monitor_chandef = *chandef;

	return 0;
}