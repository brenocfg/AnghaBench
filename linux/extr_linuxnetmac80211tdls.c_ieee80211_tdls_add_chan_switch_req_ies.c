#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {scalar_t__ data; } ;
struct TYPE_5__ {int /*<<< orphan*/  oper_class; int /*<<< orphan*/  target_channel; } ;
struct TYPE_6__ {TYPE_2__ chan_switch_req; } ;
struct ieee80211_tdls_data {TYPE_3__ u; } ;
struct ieee80211_sub_if_data {int dummy; } ;
struct cfg80211_chan_def {TYPE_1__* chan; } ;
struct TYPE_4__ {int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
#define  WLAN_EID_SECONDARY_CHANNEL_OFFSET 128 
 int /*<<< orphan*/  ieee80211_frequency_to_channel (int /*<<< orphan*/ ) ; 
 size_t ieee80211_ie_split (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ieee80211_tdls_add_link_ie (struct ieee80211_sub_if_data*,struct sk_buff*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static void
ieee80211_tdls_add_chan_switch_req_ies(struct ieee80211_sub_if_data *sdata,
				       struct sk_buff *skb, const u8 *peer,
				       bool initiator, const u8 *extra_ies,
				       size_t extra_ies_len, u8 oper_class,
				       struct cfg80211_chan_def *chandef)
{
	struct ieee80211_tdls_data *tf;
	size_t offset = 0, noffset;

	if (WARN_ON_ONCE(!chandef))
		return;

	tf = (void *)skb->data;
	tf->u.chan_switch_req.target_channel =
		ieee80211_frequency_to_channel(chandef->chan->center_freq);
	tf->u.chan_switch_req.oper_class = oper_class;

	if (extra_ies_len) {
		static const u8 before_lnkie[] = {
			WLAN_EID_SECONDARY_CHANNEL_OFFSET,
		};
		noffset = ieee80211_ie_split(extra_ies, extra_ies_len,
					     before_lnkie,
					     ARRAY_SIZE(before_lnkie),
					     offset);
		skb_put_data(skb, extra_ies + offset, noffset - offset);
		offset = noffset;
	}

	ieee80211_tdls_add_link_ie(sdata, skb, peer, initiator);

	/* add any remaining IEs */
	if (extra_ies_len) {
		noffset = extra_ies_len;
		skb_put_data(skb, extra_ies + offset, noffset - offset);
	}
}