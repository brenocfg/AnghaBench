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
struct rtl_stats {int packet_matchbssid; int packet_toself; int packet_beacon; int /*<<< orphan*/  rx_packet_bw; int /*<<< orphan*/ * rx_mimo_signalquality; int /*<<< orphan*/  signalquality; int /*<<< orphan*/  recvsignalpower; int /*<<< orphan*/  bt_rx_rssi_percentage; int /*<<< orphan*/  rx_pwdb_all; int /*<<< orphan*/  crc; int /*<<< orphan*/  icv; int /*<<< orphan*/  hwerror; int /*<<< orphan*/  rate; int /*<<< orphan*/  psaddr; } ;
struct TYPE_2__ {scalar_t__ opmode; } ;
struct rtl_priv {TYPE_1__ mac80211; } ;
struct rtl_mac {int /*<<< orphan*/  bssid; } ;
struct rtl_efuse {int /*<<< orphan*/  dev_addr; } ;
struct phy_dm_struct {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr1; int /*<<< orphan*/  addr3; int /*<<< orphan*/  addr2; int /*<<< orphan*/  frame_control; } ;
struct dm_phy_status_info {int station_id; int is_packet_match_bssid; int is_packet_to_self; int is_to_self; int is_packet_beacon; int /*<<< orphan*/  band_width; int /*<<< orphan*/ * rx_mimo_signal_quality; int /*<<< orphan*/  signal_quality; int /*<<< orphan*/  recv_signal_power; int /*<<< orphan*/  bt_rx_rssi_percentage; int /*<<< orphan*/  rx_pwdb_all; int /*<<< orphan*/  data_rate; } ;
struct dm_per_pkt_info {int station_id; int is_packet_match_bssid; int is_packet_to_self; int is_to_self; int is_packet_beacon; int /*<<< orphan*/  band_width; int /*<<< orphan*/ * rx_mimo_signal_quality; int /*<<< orphan*/  signal_quality; int /*<<< orphan*/  recv_signal_power; int /*<<< orphan*/  bt_rx_rssi_percentage; int /*<<< orphan*/  rx_pwdb_all; int /*<<< orphan*/  data_rate; } ;
typedef  int /*<<< orphan*/  pktinfo ;
typedef  int /*<<< orphan*/  phy_info ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_get_SA (struct ieee80211_hdr*) ; 
 scalar_t__ ieee80211_has_fromds (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_has_tods (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_ctl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dm_phy_status_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  odm_phy_status_query (struct phy_dm_struct*,struct dm_phy_status_info*,int /*<<< orphan*/ *,struct dm_phy_status_info*) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct phy_dm_struct* rtlpriv_to_phydm (struct rtl_priv*) ; 

__attribute__((used)) static bool rtl_phydm_query_phy_status(struct rtl_priv *rtlpriv, u8 *phystrpt,
				       struct ieee80211_hdr *hdr,
				       struct rtl_stats *pstatus)
{
	/* NOTE: phystrpt may be NULL, and need to fill default value */

	struct phy_dm_struct *dm = rtlpriv_to_phydm(rtlpriv);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtlpriv);
	struct rtl_mac *mac = rtl_mac(rtlpriv);
	struct dm_per_pkt_info pktinfo; /* input of pydm */
	struct dm_phy_status_info phy_info; /* output of phydm */
	__le16 fc = hdr->frame_control;

	/* fill driver pstatus */
	ether_addr_copy(pstatus->psaddr, ieee80211_get_SA(hdr));

	/* fill pktinfo */
	memset(&pktinfo, 0, sizeof(pktinfo));

	pktinfo.data_rate = pstatus->rate;

	if (rtlpriv->mac80211.opmode == NL80211_IFTYPE_STATION) {
		pktinfo.station_id = 0;
	} else {
		/* TODO: use rtl_find_sta() to find ID */
		pktinfo.station_id = 0xFF;
	}

	pktinfo.is_packet_match_bssid =
		(!ieee80211_is_ctl(fc) &&
		 (ether_addr_equal(mac->bssid,
				   ieee80211_has_tods(fc) ?
					   hdr->addr1 :
					   ieee80211_has_fromds(fc) ?
					   hdr->addr2 :
					   hdr->addr3)) &&
		 (!pstatus->hwerror) && (!pstatus->crc) && (!pstatus->icv));
	pktinfo.is_packet_to_self =
		pktinfo.is_packet_match_bssid &&
		(ether_addr_equal(hdr->addr1, rtlefuse->dev_addr));
	pktinfo.is_to_self = (!pstatus->icv) && (!pstatus->crc) &&
			     (ether_addr_equal(hdr->addr1, rtlefuse->dev_addr));
	pktinfo.is_packet_beacon = (ieee80211_is_beacon(fc) ? true : false);

	/* query phy status */
	if (phystrpt)
		odm_phy_status_query(dm, &phy_info, phystrpt, &pktinfo);
	else
		memset(&phy_info, 0, sizeof(phy_info));

	/* copy phy_info from phydm to driver */
	pstatus->rx_pwdb_all = phy_info.rx_pwdb_all;
	pstatus->bt_rx_rssi_percentage = phy_info.bt_rx_rssi_percentage;
	pstatus->recvsignalpower = phy_info.recv_signal_power;
	pstatus->signalquality = phy_info.signal_quality;
	pstatus->rx_mimo_signalquality[0] = phy_info.rx_mimo_signal_quality[0];
	pstatus->rx_mimo_signalquality[1] = phy_info.rx_mimo_signal_quality[1];
	pstatus->rx_packet_bw =
		phy_info.band_width; /* HT_CHANNEL_WIDTH_20 <- ODM_BW20M */

	/* fill driver pstatus */
	pstatus->packet_matchbssid = pktinfo.is_packet_match_bssid;
	pstatus->packet_toself = pktinfo.is_packet_to_self;
	pstatus->packet_beacon = pktinfo.is_packet_beacon;

	return true;
}