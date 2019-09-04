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
typedef  int u32 ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct rtl_stats {int packet_report_type; } ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
#define  C2H_PACKET 129 
 int /*<<< orphan*/  COMP_RECV ; 
 int /*<<< orphan*/  DBG_TRACE ; 
#define  NORMAL_RX 128 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rtl8822be_c2h_packet_handler (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

u32 rtl8822be_rx_command_packet(struct ieee80211_hw *hw,
				const struct rtl_stats *status,
				struct sk_buff *skb)
{
	u32 result = 0;
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	switch (status->packet_report_type) {
	case NORMAL_RX:
		result = 0;
		break;
	case C2H_PACKET:
		rtl8822be_c2h_packet_handler(hw, skb->data, (u8)skb->len);
		result = 1;
		break;
	default:
		RT_TRACE(rtlpriv, COMP_RECV, DBG_TRACE,
			 "Unknown packet type %d\n",
			 status->packet_report_type);
		break;
	}

	return result;
}