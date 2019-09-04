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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct udphdr {int dummy; } ;
struct sk_buff {int dummy; } ;
struct rtl_ps_ctl {void* last_delaylps_stamp_jiffies; } ;
struct TYPE_6__ {int is_special_data; } ;
struct TYPE_4__ {int in_4way; void* in_4way_ts; } ;
struct TYPE_5__ {TYPE_1__ btc_info; } ;
struct rtl_priv {TYPE_3__ ra; TYPE_2__ btcoexist; } ;
struct iphdr {scalar_t__ protocol; int ihl; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int COMP_RECV ; 
 int COMP_SEND ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 scalar_t__ ETH_P_ARP ; 
 scalar_t__ ETH_P_IP ; 
 scalar_t__ ETH_P_IPV6 ; 
 scalar_t__ ETH_P_PAE ; 
 scalar_t__ IPPROTO_UDP ; 
 int /*<<< orphan*/  PACKET_ARP ; 
 int /*<<< orphan*/  PACKET_DHCP ; 
 int /*<<< orphan*/  PACKET_EAPOL ; 
 int PROTOC_TYPE_SIZE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ be16_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_is_data (int /*<<< orphan*/ ) ; 
 void* jiffies ; 
 int /*<<< orphan*/  rtl_get_fc (struct sk_buff*) ; 
 int /*<<< orphan*/  rtl_lps_leave (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int* rtl_skb_ether_type_ptr (struct ieee80211_hw*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  setup_special_tx (struct rtl_priv*,struct rtl_ps_ctl*,int /*<<< orphan*/ ) ; 

u8 rtl_is_special_data(struct ieee80211_hw *hw, struct sk_buff *skb, u8 is_tx,
		       bool is_enc)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	__le16 fc = rtl_get_fc(skb);
	u16 ether_type;
	const u8 *ether_type_ptr;
	const struct iphdr *ip;

	if (!ieee80211_is_data(fc))
		goto end;

	ether_type_ptr = rtl_skb_ether_type_ptr(hw, skb, is_enc);
	ether_type = be16_to_cpup((__be16 *)ether_type_ptr);

	if (ETH_P_IP == ether_type) {
		ip = (struct iphdr *)((u8 *)ether_type_ptr +
		     PROTOC_TYPE_SIZE);
		if (IPPROTO_UDP == ip->protocol) {
			struct udphdr *udp = (struct udphdr *)((u8 *)ip +
							       (ip->ihl << 2));
			if (((((u8 *)udp)[1] == 68) &&
			     (((u8 *)udp)[3] == 67)) ||
			    ((((u8 *)udp)[1] == 67) &&
			     (((u8 *)udp)[3] == 68))) {
				/* 68 : UDP BOOTP client
				 * 67 : UDP BOOTP server
				 */
				RT_TRACE(rtlpriv, (COMP_SEND | COMP_RECV),
					 DBG_DMESG, "dhcp %s !!\n",
					 (is_tx) ? "Tx" : "Rx");

				if (is_tx)
					setup_special_tx(rtlpriv, ppsc,
							 PACKET_DHCP);

				return true;
			}
		}
	} else if (ETH_P_ARP == ether_type) {
		if (is_tx)
			setup_special_tx(rtlpriv, ppsc, PACKET_ARP);

		return true;
	} else if (ETH_P_PAE == ether_type) {
		/* EAPOL is seens as in-4way */
		rtlpriv->btcoexist.btc_info.in_4way = true;
		rtlpriv->btcoexist.btc_info.in_4way_ts = jiffies;

		RT_TRACE(rtlpriv, (COMP_SEND | COMP_RECV), DBG_DMESG,
			 "802.1X %s EAPOL pkt!!\n", (is_tx) ? "Tx" : "Rx");

		if (is_tx) {
			rtlpriv->ra.is_special_data = true;
			rtl_lps_leave(hw);
			ppsc->last_delaylps_stamp_jiffies = jiffies;

			setup_special_tx(rtlpriv, ppsc, PACKET_EAPOL);
		}

		return true;
	} else if (ETH_P_IPV6 == ether_type) {
		/* TODO: Handle any IPv6 cases that need special handling.
		 * For now, always return false
		 */
		goto end;
	}

end:
	rtlpriv->ra.is_special_data = false;
	return false;
}