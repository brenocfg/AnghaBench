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
typedef  int u8 ;
struct TYPE_2__ {scalar_t__ link_state; int /*<<< orphan*/  vif; int /*<<< orphan*/  bssid; } ;
struct rtl_phy {scalar_t__ max_ht_chan_bw; } ;
struct rtl_priv {TYPE_1__ mac80211; struct rtl_phy phy; } ;
struct rtl_beacon_keys {int valid; int bcn_channel; int ht_info_infos_0_sco; int /*<<< orphan*/  ht_cap_info; } ;
struct rtl_mac {scalar_t__ opmode; int new_beacon_cnt; struct rtl_beacon_keys cur_beacon_keys; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_ht_operation {int primary_chan; int ht_param; } ;
struct ieee80211_ht_cap {int /*<<< orphan*/  cap_info; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr3; int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  bcn_key ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BEACON ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int FCS_LEN ; 
 scalar_t__ HT_CHANNEL_WIDTH_20_40 ; 
 scalar_t__ MAC80211_LINKED ; 
 scalar_t__ MAC80211_LINKED_SCANNING ; 
 scalar_t__ MAC80211_NOLINK ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  WLAN_EID_DS_PARAMS ; 
 int /*<<< orphan*/  WLAN_EID_HT_CAPABILITY ; 
 int /*<<< orphan*/  WLAN_EID_HT_OPERATION ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_connection_loss (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (struct rtl_beacon_keys*,struct rtl_beacon_keys*,int) ; 
 int /*<<< orphan*/  memcpy (struct rtl_beacon_keys*,struct rtl_beacon_keys*,int) ; 
 int* rtl_find_ie (void*,unsigned int,int /*<<< orphan*/ ) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

bool rtl_check_beacon_key(struct ieee80211_hw *hw, void *data, unsigned int len)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	struct ieee80211_hdr *hdr = data;
	struct ieee80211_ht_cap *ht_cap_ie;
	struct ieee80211_ht_operation *ht_oper_ie = NULL;
	struct rtl_beacon_keys bcn_key = {};
	struct rtl_beacon_keys *cur_bcn_key;
	u8 *ht_cap;
	u8 ht_cap_len;
	u8 *ht_oper;
	u8 ht_oper_len;
	u8 *ds_param;
	u8 ds_param_len;

	if (mac->opmode != NL80211_IFTYPE_STATION)
		return false;

	/* check if this really is a beacon*/
	if (!ieee80211_is_beacon(hdr->frame_control))
		return false;

	/* min. beacon length + FCS_LEN */
	if (len <= 40 + FCS_LEN)
		return false;

	cur_bcn_key = &mac->cur_beacon_keys;

	if (rtlpriv->mac80211.link_state == MAC80211_NOLINK) {
		if (cur_bcn_key->valid) {
			cur_bcn_key->valid = false;
			RT_TRACE(rtlpriv, COMP_BEACON, DBG_LOUD,
				 "Reset cur_beacon_keys.valid to false!\n");
		}
		return false;
	}

	/* and only beacons from the associated BSSID, please */
	if (!ether_addr_equal(hdr->addr3, rtlpriv->mac80211.bssid))
		return false;

	/***** Parsing DS Param IE ******/
	ds_param = rtl_find_ie(data, len - FCS_LEN, WLAN_EID_DS_PARAMS);

	if (ds_param && !(ds_param[1] < sizeof(*ds_param))) {
		ds_param_len = ds_param[1];
		bcn_key.bcn_channel = ds_param[2];
	} else {
		ds_param = NULL;
	}

	/***** Parsing HT Cap. IE ******/
	ht_cap = rtl_find_ie(data, len - FCS_LEN, WLAN_EID_HT_CAPABILITY);

	if (ht_cap && !(ht_cap[1] < sizeof(*ht_cap))) {
		ht_cap_len = ht_cap[1];
		ht_cap_ie = (struct ieee80211_ht_cap *)&ht_cap[2];
		bcn_key.ht_cap_info = ht_cap_ie->cap_info;
	} else  {
		ht_cap = NULL;
	}

	/***** Parsing HT Info. IE ******/
	ht_oper = rtl_find_ie(data, len - FCS_LEN, WLAN_EID_HT_OPERATION);

	if (ht_oper && !(ht_oper[1] < sizeof(*ht_oper))) {
		ht_oper_len = ht_oper[1];
		ht_oper_ie = (struct ieee80211_ht_operation *)&ht_oper[2];
	} else {
		ht_oper = NULL;
	}

	/* update bcn_key */

	if (!ds_param && ht_oper && ht_oper_ie)
		bcn_key.bcn_channel = ht_oper_ie->primary_chan;

	if (ht_oper && ht_oper_ie)
		bcn_key.ht_info_infos_0_sco = ht_oper_ie->ht_param & 0x03;

	bcn_key.valid = true;

	/* update cur_beacon_keys or compare beacon key */
	if (rtlpriv->mac80211.link_state != MAC80211_LINKED &&
	    rtlpriv->mac80211.link_state != MAC80211_LINKED_SCANNING)
		return true;

	if (!cur_bcn_key->valid) {
		/* update cur_beacon_keys */
		memcpy(cur_bcn_key, &bcn_key, sizeof(bcn_key));
		cur_bcn_key->valid = true;

		RT_TRACE(rtlpriv, COMP_BEACON, DBG_LOUD,
			 "Beacon key update!ch=%d, ht_cap_info=0x%x, sco=0x%x\n",
			 cur_bcn_key->bcn_channel,
			 cur_bcn_key->ht_cap_info,
			 cur_bcn_key->ht_info_infos_0_sco);
		return true;
	}

	/* compare beacon key */
	if (!memcmp(cur_bcn_key, &bcn_key, sizeof(bcn_key))) {
		/* same beacon key */
		mac->new_beacon_cnt = 0;
		goto chk_exit;
	}

	if (cur_bcn_key->bcn_channel == bcn_key.bcn_channel &&
	    cur_bcn_key->ht_cap_info == bcn_key.ht_cap_info) {
		/* Beacon HT info IE, secondary channel offset check */
		/* 40M -> 20M */
		if (cur_bcn_key->ht_info_infos_0_sco >
		    bcn_key.ht_info_infos_0_sco) {
			/* Not a new beacon */
			RT_TRACE(rtlpriv, COMP_BEACON, DBG_DMESG,
				 "Beacon BW change! sco:0x%x -> 0x%x\n",
				 cur_bcn_key->ht_info_infos_0_sco,
				 bcn_key.ht_info_infos_0_sco);

			cur_bcn_key->ht_info_infos_0_sco =
					bcn_key.ht_info_infos_0_sco;
		} else {
			/* 20M -> 40M */
			if (rtlphy->max_ht_chan_bw >= HT_CHANNEL_WIDTH_20_40) {
				/* Not a new beacon */
				RT_TRACE(rtlpriv, COMP_BEACON, DBG_DMESG,
					 "Beacon BW change! sco:0x%x -> 0x%x\n",
					 cur_bcn_key->ht_info_infos_0_sco,
					 bcn_key.ht_info_infos_0_sco);

				cur_bcn_key->ht_info_infos_0_sco =
					bcn_key.ht_info_infos_0_sco;
			} else {
				mac->new_beacon_cnt++;
			}
		}
	} else {
		mac->new_beacon_cnt++;
	}

	if (mac->new_beacon_cnt == 1) {
		RT_TRACE(rtlpriv, COMP_BEACON, DBG_DMESG,
			 "Get new beacon.\n");
		RT_TRACE(rtlpriv, COMP_BEACON, DBG_DMESG,
			 "Cur : ch=%d, ht_cap=0x%x, sco=0x%x\n",
			 cur_bcn_key->bcn_channel,
			 cur_bcn_key->ht_cap_info,
			 cur_bcn_key->ht_info_infos_0_sco);
		RT_TRACE(rtlpriv, COMP_BEACON, DBG_DMESG,
			 "New RX : ch=%d, ht_cap=0x%x, sco=0x%x\n",
			 bcn_key.bcn_channel,
			 bcn_key.ht_cap_info,
			 bcn_key.ht_info_infos_0_sco);

	} else if (mac->new_beacon_cnt > 1) {
		RT_TRACE(rtlpriv, COMP_BEACON, DBG_DMESG,
			 "new beacon cnt: %d\n",
			 mac->new_beacon_cnt);
	}

	if (mac->new_beacon_cnt > 3) {
		ieee80211_connection_loss(rtlpriv->mac80211.vif);
		RT_TRACE(rtlpriv, COMP_BEACON, DBG_DMESG,
			 "new beacon cnt >3, disconnect !\n");
	}

chk_exit:

	return true;
}