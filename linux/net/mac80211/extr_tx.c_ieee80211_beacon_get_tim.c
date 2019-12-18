#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_supported_band {int dummy; } ;
struct ieee80211_mutable_offsets {int /*<<< orphan*/  tim_length; int /*<<< orphan*/  tim_offset; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  monitors; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEACON_TX_STATUS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* __ieee80211_beacon_get (struct ieee80211_hw*,struct ieee80211_vif*,struct ieee80211_mutable_offsets*,int) ; 
 TYPE_1__* hw_to_local (struct ieee80211_hw*) ; 
 struct ieee80211_supported_band* ieee80211_get_sband (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_hw_check (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_tx_monitor (TYPE_1__*,struct sk_buff*,struct ieee80211_supported_band*,int,int,int,int /*<<< orphan*/ *) ; 
 int ieee80211_vif_get_shift (struct ieee80211_vif*) ; 
 struct sk_buff* skb_copy (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vif_to_sdata (struct ieee80211_vif*) ; 

struct sk_buff *ieee80211_beacon_get_tim(struct ieee80211_hw *hw,
					 struct ieee80211_vif *vif,
					 u16 *tim_offset, u16 *tim_length)
{
	struct ieee80211_mutable_offsets offs = {};
	struct sk_buff *bcn = __ieee80211_beacon_get(hw, vif, &offs, false);
	struct sk_buff *copy;
	struct ieee80211_supported_band *sband;
	int shift;

	if (!bcn)
		return bcn;

	if (tim_offset)
		*tim_offset = offs.tim_offset;

	if (tim_length)
		*tim_length = offs.tim_length;

	if (ieee80211_hw_check(hw, BEACON_TX_STATUS) ||
	    !hw_to_local(hw)->monitors)
		return bcn;

	/* send a copy to monitor interfaces */
	copy = skb_copy(bcn, GFP_ATOMIC);
	if (!copy)
		return bcn;

	shift = ieee80211_vif_get_shift(vif);
	sband = ieee80211_get_sband(vif_to_sdata(vif));
	if (!sband)
		return bcn;

	ieee80211_tx_monitor(hw_to_local(hw), copy, sband, 1, shift, false,
			     NULL);

	return bcn;
}