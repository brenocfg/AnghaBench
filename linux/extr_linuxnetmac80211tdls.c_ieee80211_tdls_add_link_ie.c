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
struct sk_buff {int dummy; } ;
struct ieee80211_tdls_lnkie {int ie_len; int /*<<< orphan*/  resp_sta; int /*<<< orphan*/  init_sta; int /*<<< orphan*/  bssid; int /*<<< orphan*/  ie_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  const* bssid; } ;
struct TYPE_6__ {TYPE_2__ mgd; } ;
struct TYPE_4__ {int /*<<< orphan*/ * addr; } ;
struct ieee80211_sub_if_data {TYPE_3__ u; TYPE_1__ vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  WLAN_EID_LINK_ID ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct ieee80211_tdls_lnkie* skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static void ieee80211_tdls_add_link_ie(struct ieee80211_sub_if_data *sdata,
				       struct sk_buff *skb, const u8 *peer,
				       bool initiator)
{
	struct ieee80211_tdls_lnkie *lnkid;
	const u8 *init_addr, *rsp_addr;

	if (initiator) {
		init_addr = sdata->vif.addr;
		rsp_addr = peer;
	} else {
		init_addr = peer;
		rsp_addr = sdata->vif.addr;
	}

	lnkid = skb_put(skb, sizeof(struct ieee80211_tdls_lnkie));

	lnkid->ie_type = WLAN_EID_LINK_ID;
	lnkid->ie_len = sizeof(struct ieee80211_tdls_lnkie) - 2;

	memcpy(lnkid->bssid, sdata->u.mgd.bssid, ETH_ALEN);
	memcpy(lnkid->init_sta, init_addr, ETH_ALEN);
	memcpy(lnkid->resp_sta, rsp_addr, ETH_ALEN);
}