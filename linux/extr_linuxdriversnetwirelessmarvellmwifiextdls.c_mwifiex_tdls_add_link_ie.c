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
struct sk_buff {int dummy; } ;
struct ieee_types_header {int dummy; } ;
struct ieee80211_tdls_lnkie {int ie_len; int /*<<< orphan*/  resp_sta; int /*<<< orphan*/  init_sta; int /*<<< orphan*/  bssid; int /*<<< orphan*/  ie_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  WLAN_EID_LINK_ID ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct ieee80211_tdls_lnkie* skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static void
mwifiex_tdls_add_link_ie(struct sk_buff *skb, const u8 *src_addr,
			 const u8 *peer, const u8 *bssid)
{
	struct ieee80211_tdls_lnkie *lnkid;

	lnkid = skb_put(skb, sizeof(struct ieee80211_tdls_lnkie));
	lnkid->ie_type = WLAN_EID_LINK_ID;
	lnkid->ie_len = sizeof(struct ieee80211_tdls_lnkie) -
			sizeof(struct ieee_types_header);

	memcpy(lnkid->bssid, bssid, ETH_ALEN);
	memcpy(lnkid->init_sta, src_addr, ETH_ALEN);
	memcpy(lnkid->resp_sta, peer, ETH_ALEN);
}