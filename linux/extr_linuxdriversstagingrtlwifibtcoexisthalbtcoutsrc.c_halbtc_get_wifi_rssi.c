#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int undec_sm_pwdb; } ;
struct TYPE_3__ {scalar_t__ link_state; } ;
struct rtl_priv {TYPE_2__ dm; TYPE_1__ mac80211; } ;
typedef  int s32 ;

/* Variables and functions */
 scalar_t__ MAC80211_LINKED ; 

__attribute__((used)) static s32 halbtc_get_wifi_rssi(struct rtl_priv *rtlpriv)
{
	int undec_sm_pwdb = 0;

	if (rtlpriv->mac80211.link_state >= MAC80211_LINKED)
		undec_sm_pwdb = rtlpriv->dm.undec_sm_pwdb;
	else /* associated entry pwdb */
		undec_sm_pwdb = rtlpriv->dm.undec_sm_pwdb;
	return undec_sm_pwdb;
}