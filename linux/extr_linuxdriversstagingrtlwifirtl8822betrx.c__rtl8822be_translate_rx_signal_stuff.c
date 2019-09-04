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
typedef  int u16 ;
struct sk_buff {int /*<<< orphan*/ * data; } ;
struct rtl_stats {int rx_drvinfo_size; int rx_bufshift; scalar_t__ packet_matchbssid; scalar_t__ packet_beacon; } ;
struct ieee80211_qos_hdr {int /*<<< orphan*/  qos_ctrl; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_non_be_pkt; int /*<<< orphan*/  num_qry_beacon_pkt; } ;
struct TYPE_5__ {TYPE_1__ dbginfo; } ;
struct TYPE_6__ {TYPE_2__ dm; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rtl8822be_query_rxphystatus (struct ieee80211_hw*,int /*<<< orphan*/ *,struct ieee80211_hdr*,struct rtl_stats*) ; 
 int /*<<< orphan*/  ieee80211_get_DA (struct ieee80211_hdr*) ; 
 scalar_t__ ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_3__* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_process_phyinfo (struct ieee80211_hw*,int /*<<< orphan*/ *,struct rtl_stats*) ; 

__attribute__((used)) static void _rtl8822be_translate_rx_signal_stuff(struct ieee80211_hw *hw,
						 struct sk_buff *skb,
						 struct rtl_stats *pstatus,
						 u8 *p_phystrpt)
{
	struct ieee80211_hdr *hdr;
	u8 *tmp_buf;

	tmp_buf = skb->data + pstatus->rx_drvinfo_size + pstatus->rx_bufshift +
		  24;

	hdr = (struct ieee80211_hdr *)tmp_buf;

	/* query phy status */
	_rtl8822be_query_rxphystatus(hw, p_phystrpt, hdr, pstatus);

	/* packet statistics */
	if (pstatus->packet_beacon && pstatus->packet_matchbssid)
		rtl_priv(hw)->dm.dbginfo.num_qry_beacon_pkt++;

	if (pstatus->packet_matchbssid &&
	    ieee80211_is_data_qos(hdr->frame_control) &&
	    !is_multicast_ether_addr(ieee80211_get_DA(hdr))) {
		struct ieee80211_qos_hdr *hdr_qos =
			(struct ieee80211_qos_hdr *)tmp_buf;
		u16 tid = le16_to_cpu(hdr_qos->qos_ctrl) & 0xf;

		if (tid != 0 && tid != 3)
			rtl_priv(hw)->dm.dbginfo.num_non_be_pkt++;
	}

	/* signal statistics */
	if (p_phystrpt)
		rtl_process_phyinfo(hw, tmp_buf, pstatus);
}