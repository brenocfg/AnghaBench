#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct ieee80211_vht_cap {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  cap; int /*<<< orphan*/  vht_supported; } ;
struct ieee80211_supported_band {TYPE_4__ vht_cap; } ;
struct TYPE_5__ {scalar_t__ width; } ;
struct TYPE_6__ {TYPE_1__ chandef; } ;
struct TYPE_7__ {TYPE_2__ bss_conf; } ;
struct ieee80211_sub_if_data {TYPE_3__ vif; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ NL80211_CHAN_WIDTH_10 ; 
 scalar_t__ NL80211_CHAN_WIDTH_20_NOHT ; 
 scalar_t__ NL80211_CHAN_WIDTH_5 ; 
 struct ieee80211_supported_band* ieee80211_get_sband (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_ie_build_vht_cap (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * skb_put (struct sk_buff*,int) ; 
 int skb_tailroom (struct sk_buff*) ; 

int mesh_add_vht_cap_ie(struct ieee80211_sub_if_data *sdata,
			struct sk_buff *skb)
{
	struct ieee80211_supported_band *sband;
	u8 *pos;

	sband = ieee80211_get_sband(sdata);
	if (!sband)
		return -EINVAL;

	if (!sband->vht_cap.vht_supported ||
	    sdata->vif.bss_conf.chandef.width == NL80211_CHAN_WIDTH_20_NOHT ||
	    sdata->vif.bss_conf.chandef.width == NL80211_CHAN_WIDTH_5 ||
	    sdata->vif.bss_conf.chandef.width == NL80211_CHAN_WIDTH_10)
		return 0;

	if (skb_tailroom(skb) < 2 + sizeof(struct ieee80211_vht_cap))
		return -ENOMEM;

	pos = skb_put(skb, 2 + sizeof(struct ieee80211_vht_cap));
	ieee80211_ie_build_vht_cap(pos, &sband->vht_cap, sband->vht_cap.cap);

	return 0;
}