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
typedef  int /*<<< orphan*/  u8 ;
struct wiphy {int dummy; } ;
struct wil6210_priv {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*) ; 
 struct wil6210_priv* wiphy_to_wil (struct wiphy*) ; 

__attribute__((used)) static int wil_cfg80211_set_default_key(struct wiphy *wiphy,
					struct net_device *ndev,
					u8 key_index, bool unicast,
					bool multicast)
{
	struct wil6210_priv *wil = wiphy_to_wil(wiphy);

	wil_dbg_misc(wil, "set_default_key: entered\n");
	return 0;
}