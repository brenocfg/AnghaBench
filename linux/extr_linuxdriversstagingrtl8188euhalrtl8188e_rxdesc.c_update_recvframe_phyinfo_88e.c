#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sta_priv {int dummy; } ;
struct sta_info {int mac_id; } ;
struct rx_pkt_attrib {int /*<<< orphan*/  mcs_rate; int /*<<< orphan*/  crc_err; int /*<<< orphan*/  icv_err; int /*<<< orphan*/  phy_info; } ;
struct recv_frame {struct sta_info* psta; TYPE_1__* pkt; struct rx_pkt_attrib attrib; struct adapter* adapter; } ;
struct phy_stat {int dummy; } ;
struct odm_phy_status_info {int dummy; } ;
struct odm_per_pkt_info {int bPacketMatchBSSID; int bPacketToSelf; int bPacketBeacon; int StationID; int /*<<< orphan*/  Rate; } ;
struct TYPE_8__ {int /*<<< orphan*/ * MacAddress; } ;
struct TYPE_9__ {TYPE_2__ network; } ;
struct TYPE_11__ {TYPE_3__ cur_network; } ;
struct adapter {TYPE_5__ mlmepriv; TYPE_4__* HalData; struct sta_priv stapriv; int /*<<< orphan*/  eeprompriv; } ;
struct TYPE_10__ {int /*<<< orphan*/  odmpriv; } ;
struct TYPE_7__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ GetFrameSubType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsFrameTypeCtrl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ODM_PhyStatusQuery (int /*<<< orphan*/ *,struct odm_phy_status_info*,int /*<<< orphan*/ *,struct odm_per_pkt_info*) ; 
 int WIFI_ADHOC_MASTER_STATE ; 
 int WIFI_ADHOC_STATE ; 
 int WIFI_AP_STATE ; 
 scalar_t__ WIFI_BEACON ; 
 int WIFI_STATION_STATE ; 
 scalar_t__ check_fwstate (TYPE_5__*,int) ; 
 int /*<<< orphan*/  get_bssid (TYPE_5__*) ; 
 int /*<<< orphan*/  get_da (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_hdr_bssid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_sa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  myid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl8188e_process_phy_info (struct adapter*,struct recv_frame*) ; 
 struct sta_info* rtw_get_stainfo (struct sta_priv*,int /*<<< orphan*/ *) ; 

void update_recvframe_phyinfo_88e(struct recv_frame *precvframe,
				  struct phy_stat *pphy_status)
{
	struct adapter *padapter = precvframe->adapter;
	struct rx_pkt_attrib *pattrib = &precvframe->attrib;
	struct odm_phy_status_info *pPHYInfo  = (struct odm_phy_status_info *)(&pattrib->phy_info);
	u8 *wlanhdr;
	struct odm_per_pkt_info	pkt_info;
	u8 *sa = NULL;
	struct sta_priv *pstapriv;
	struct sta_info *psta;

	pkt_info.bPacketMatchBSSID = false;
	pkt_info.bPacketToSelf = false;
	pkt_info.bPacketBeacon = false;

	wlanhdr = precvframe->pkt->data;

	pkt_info.bPacketMatchBSSID = ((!IsFrameTypeCtrl(wlanhdr)) &&
		!pattrib->icv_err && !pattrib->crc_err &&
		!memcmp(get_hdr_bssid(wlanhdr),
		 get_bssid(&padapter->mlmepriv), ETH_ALEN));

	pkt_info.bPacketToSelf = pkt_info.bPacketMatchBSSID &&
				 (!memcmp(get_da(wlanhdr),
				  myid(&padapter->eeprompriv), ETH_ALEN));

	pkt_info.bPacketBeacon = pkt_info.bPacketMatchBSSID &&
				 (GetFrameSubType(wlanhdr) == WIFI_BEACON);

	if (pkt_info.bPacketBeacon) {
		if (check_fwstate(&padapter->mlmepriv, WIFI_STATION_STATE))
			sa = padapter->mlmepriv.cur_network.network.MacAddress;
		/* to do Ad-hoc */
	} else {
		sa = get_sa(wlanhdr);
	}

	pstapriv = &padapter->stapriv;
	pkt_info.StationID = 0xFF;
	psta = rtw_get_stainfo(pstapriv, sa);
	if (psta)
		pkt_info.StationID = psta->mac_id;
	pkt_info.Rate = pattrib->mcs_rate;

	ODM_PhyStatusQuery(&padapter->HalData->odmpriv, pPHYInfo,
			   (u8 *)pphy_status, &(pkt_info));

	precvframe->psta = NULL;
	if (pkt_info.bPacketMatchBSSID &&
	    (check_fwstate(&padapter->mlmepriv, WIFI_AP_STATE))) {
		if (psta) {
			precvframe->psta = psta;
			rtl8188e_process_phy_info(padapter, precvframe);
		}
	} else if (pkt_info.bPacketToSelf || pkt_info.bPacketBeacon) {
		if (check_fwstate(&padapter->mlmepriv, WIFI_ADHOC_STATE|WIFI_ADHOC_MASTER_STATE)) {
			if (psta)
				precvframe->psta = psta;
		}
		rtl8188e_process_phy_info(padapter, precvframe);
	}
}