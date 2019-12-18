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
struct sk_buff {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_mutable_offsets {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct sk_buff* __ieee80211_beacon_get (struct ieee80211_hw*,struct ieee80211_vif*,struct ieee80211_mutable_offsets*,int) ; 

struct sk_buff *
ieee80211_beacon_get_template(struct ieee80211_hw *hw,
			      struct ieee80211_vif *vif,
			      struct ieee80211_mutable_offsets *offs)
{
	return __ieee80211_beacon_get(hw, vif, offs, true);
}