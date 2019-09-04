#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct ieee80211_if_managed {int /*<<< orphan*/  aid; } ;
struct TYPE_2__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_AID ; 
 int /*<<< orphan*/  put_unaligned_le16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static void
ieee80211_tdls_add_aid(struct ieee80211_sub_if_data *sdata, struct sk_buff *skb)
{
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	u8 *pos = skb_put(skb, 4);

	*pos++ = WLAN_EID_AID;
	*pos++ = 2; /* len */
	put_unaligned_le16(ifmgd->aid, pos);
}