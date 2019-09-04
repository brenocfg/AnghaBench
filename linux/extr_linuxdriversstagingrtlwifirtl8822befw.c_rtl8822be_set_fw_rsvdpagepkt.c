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
typedef  int /*<<< orphan*/  u1_rsvd_page_loc ;
struct sk_buff {int dummy; } ;
struct rtl_priv {int dummy; } ;
struct rtl_mac {int assoc_id; int /*<<< orphan*/  bssid; int /*<<< orphan*/  mac_addr; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BEACON_PG ; 
 int /*<<< orphan*/  BEACON_QUEUE ; 
 int BT_QOS_NULL_PG ; 
 int /*<<< orphan*/  COMP_CMD ; 
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  COMP_POWER ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  DBG_WARNING ; 
 int /*<<< orphan*/  H2C_8822B_RSVDPAGE ; 
 int NULL_PG ; 
 int PROBERSP_PG ; 
 int PSPOLL_PG ; 
 int QOS_NULL_PG ; 
 int /*<<< orphan*/  RT_PRINT_DATA (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SET_80211_HDR_ADDRESS1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_80211_HDR_ADDRESS2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_80211_HDR_ADDRESS3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_80211_PS_POLL_AID (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_80211_PS_POLL_BSSID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_80211_PS_POLL_TA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_H2CCMD_RSVDPAGE_LOC_BT_QOS_NULL_DATA (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_H2CCMD_RSVDPAGE_LOC_NULL_DATA (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_H2CCMD_RSVDPAGE_LOC_PROBE_RSP (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_H2CCMD_RSVDPAGE_LOC_PSPOLL (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_H2CCMD_RSVDPAGE_LOC_QOS_NULL_DATA (int /*<<< orphan*/ *,int) ; 
 int TOTAL_RESERVED_PKT_LEN ; 
 int _rtl8822be_send_bcn_or_cmd_packet (struct ieee80211_hw*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * reserved_page_packet ; 
 int /*<<< orphan*/  rtl8822be_fill_h2c_cmd (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 scalar_t__ skb_put (struct sk_buff*,int) ; 

void rtl8822be_set_fw_rsvdpagepkt(struct ieee80211_hw *hw, bool b_dl_finished)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct sk_buff *skb = NULL;

	u32 totalpacketlen;
	bool rtstatus;
	u8 u1_rsvd_page_loc[7] = {0};
	bool b_dlok = false;

	u8 *beacon;
	u8 *p_pspoll;
	u8 *nullfunc;
	u8 *p_probersp;
	u8 *qosnull;
	u8 *btqosnull;

	memset(u1_rsvd_page_loc, 0, sizeof(u1_rsvd_page_loc));

	/*---------------------------------------------------------
	 *			(1) beacon
	 *---------------------------------------------------------
	 */
	beacon = &reserved_page_packet[BEACON_PG * 128];
	SET_80211_HDR_ADDRESS2(beacon, mac->mac_addr);
	SET_80211_HDR_ADDRESS3(beacon, mac->bssid);

	/*-------------------------------------------------------
	 *			(2) ps-poll
	 *--------------------------------------------------------
	 */
	p_pspoll = &reserved_page_packet[PSPOLL_PG * 128];
	SET_80211_PS_POLL_AID(p_pspoll, (mac->assoc_id | 0xc000));
	SET_80211_PS_POLL_BSSID(p_pspoll, mac->bssid);
	SET_80211_PS_POLL_TA(p_pspoll, mac->mac_addr);

	SET_H2CCMD_RSVDPAGE_LOC_PSPOLL(u1_rsvd_page_loc, PSPOLL_PG);

	/*--------------------------------------------------------
	 *			(3) null data
	 *---------------------------------------------------------
	 */
	nullfunc = &reserved_page_packet[NULL_PG * 128];
	SET_80211_HDR_ADDRESS1(nullfunc, mac->bssid);
	SET_80211_HDR_ADDRESS2(nullfunc, mac->mac_addr);
	SET_80211_HDR_ADDRESS3(nullfunc, mac->bssid);

	SET_H2CCMD_RSVDPAGE_LOC_NULL_DATA(u1_rsvd_page_loc, NULL_PG);

	/*---------------------------------------------------------
	 *			(4) probe response
	 *----------------------------------------------------------
	 */
	p_probersp = &reserved_page_packet[PROBERSP_PG * 128];
	SET_80211_HDR_ADDRESS1(p_probersp, mac->bssid);
	SET_80211_HDR_ADDRESS2(p_probersp, mac->mac_addr);
	SET_80211_HDR_ADDRESS3(p_probersp, mac->bssid);

	SET_H2CCMD_RSVDPAGE_LOC_PROBE_RSP(u1_rsvd_page_loc, PROBERSP_PG);

	/*---------------------------------------------------------
	 *			(5) QoS null data
	 *----------------------------------------------------------
	 */
	qosnull = &reserved_page_packet[QOS_NULL_PG * 128];
	SET_80211_HDR_ADDRESS1(qosnull, mac->bssid);
	SET_80211_HDR_ADDRESS2(qosnull, mac->mac_addr);
	SET_80211_HDR_ADDRESS3(qosnull, mac->bssid);

	SET_H2CCMD_RSVDPAGE_LOC_QOS_NULL_DATA(u1_rsvd_page_loc, QOS_NULL_PG);

	/*---------------------------------------------------------
	 *			(6) BT QoS null data
	 *----------------------------------------------------------
	 */
	btqosnull = &reserved_page_packet[BT_QOS_NULL_PG * 128];
	SET_80211_HDR_ADDRESS1(btqosnull, mac->bssid);
	SET_80211_HDR_ADDRESS2(btqosnull, mac->mac_addr);
	SET_80211_HDR_ADDRESS3(btqosnull, mac->bssid);

	SET_H2CCMD_RSVDPAGE_LOC_BT_QOS_NULL_DATA(u1_rsvd_page_loc,
						 BT_QOS_NULL_PG);

	totalpacketlen = TOTAL_RESERVED_PKT_LEN;

	RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_LOUD,
		      "rtl8822be_set_fw_rsvdpagepkt(): HW_VAR_SET_TX_CMD: ALL\n",
		      &reserved_page_packet[0], totalpacketlen);
	RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_LOUD,
		      "rtl8822be_set_fw_rsvdpagepkt(): HW_VAR_SET_TX_CMD: ALL\n",
		      u1_rsvd_page_loc, 3);

	skb = dev_alloc_skb(totalpacketlen);
	memcpy((u8 *)skb_put(skb, totalpacketlen), &reserved_page_packet,
	       totalpacketlen);

	rtstatus = _rtl8822be_send_bcn_or_cmd_packet(hw, skb, BEACON_QUEUE);

	if (rtstatus)
		b_dlok = true;

	if (b_dlok) {
		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
			 "Set RSVD page location to Fw.\n");
		RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_LOUD, "H2C_RSVDPAGE:\n",
			      u1_rsvd_page_loc, 3);
		rtl8822be_fill_h2c_cmd(hw, H2C_8822B_RSVDPAGE,
				       sizeof(u1_rsvd_page_loc),
				       u1_rsvd_page_loc);
	} else {
		RT_TRACE(rtlpriv, COMP_ERR, DBG_WARNING,
			 "Set RSVD page location to Fw FAIL!!!!!!.\n");
	}
}