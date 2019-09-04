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
typedef  int /*<<< orphan*/  u64 ;
struct wireless_dev {int /*<<< orphan*/  iftype; } ;
struct wiphy {int dummy; } ;
struct wil6210_priv {int dummy; } ;
struct ieee80211_channel {int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int wil_p2p_listen (struct wil6210_priv*,struct wireless_dev*,unsigned int,struct ieee80211_channel*,int /*<<< orphan*/ *) ; 
 struct wil6210_priv* wiphy_to_wil (struct wiphy*) ; 

__attribute__((used)) static int wil_remain_on_channel(struct wiphy *wiphy,
				 struct wireless_dev *wdev,
				 struct ieee80211_channel *chan,
				 unsigned int duration,
				 u64 *cookie)
{
	struct wil6210_priv *wil = wiphy_to_wil(wiphy);
	int rc;

	wil_dbg_misc(wil,
		     "remain_on_channel: center_freq=%d, duration=%d iftype=%d\n",
		     chan->center_freq, duration, wdev->iftype);

	rc = wil_p2p_listen(wil, wdev, duration, chan, cookie);
	return rc;
}