#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int len; int /*<<< orphan*/ * rx_data; } ;
struct TYPE_14__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
typedef  int uint ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sta_priv {int dummy; } ;
struct sta_info {int dummy; } ;
struct rtw_ieee80211_hdr_3addr {int dummy; } ;
struct TYPE_15__ {scalar_t__ state; } ;
struct mlme_ext_info {int state; TYPE_4__* FW_sta_info; int /*<<< orphan*/  assoc_AP_vendor; int /*<<< orphan*/  network; } ;
struct mlme_ext_priv {TYPE_3__ sitesurvey_res; struct mlme_ext_info mlmext_info; } ;
struct TYPE_17__ {struct sta_priv stapriv; struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_5__ _adapter ;
struct TYPE_16__ {scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GetAddr2Ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetAddr3Ptr (int /*<<< orphan*/ *) ; 
 int NUM_STA ; 
 scalar_t__ SCAN_PROCESS ; 
 int WIFI_FW_ADHOC_STATE ; 
 int WIFI_FW_ASSOC_SUCCESS ; 
 int WIFI_FW_AUTH_NULL ; 
 int WIFI_FW_STATION_STATE ; 
 int WLAN_HDR_A3_LEN ; 
 int _BEACON_IE_OFFSET_ ; 
 scalar_t__ _FAIL ; 
 unsigned int _SUCCESS ; 
 scalar_t__ _rtw_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int allocate_fw_sta_entry (TYPE_5__*) ; 
 int /*<<< orphan*/  check_assoc_AP (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_my_bssid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  report_add_sta_event (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  report_survey_event (TYPE_5__*,union recv_frame*) ; 
 struct sta_info* rtw_get_stainfo (struct sta_priv*,int /*<<< orphan*/ ) ; 
 int sta_rx_pkts (struct sta_info*) ; 
 int /*<<< orphan*/  start_clnt_auth (TYPE_5__*) ; 
 int /*<<< orphan*/  update_TSF (struct mlme_ext_priv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  update_beacon_info (TYPE_5__*,int /*<<< orphan*/ *,int,struct sta_info*) ; 
 scalar_t__ update_sta_support_rate (TYPE_5__*,int /*<<< orphan*/ *,int,int) ; 

unsigned int OnBeacon(_adapter *padapter, union recv_frame *precv_frame)
{
	int cam_idx;
	struct sta_info	*psta;
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	struct sta_priv	*pstapriv = &padapter->stapriv;
	u8 *pframe = precv_frame->u.hdr.rx_data;
	uint len = precv_frame->u.hdr.len;
	u8 *p = NULL;
	u32 ielen = 0;

#ifdef CONFIG_ATTEMPT_TO_FIX_AP_BEACON_ERROR
	p = rtw_get_ie(pframe + sizeof(struct rtw_ieee80211_hdr_3addr) + _BEACON_IE_OFFSET_, _EXT_SUPPORTEDRATES_IE_, &ielen, precv_frame->u.hdr.len -sizeof(struct rtw_ieee80211_hdr_3addr) - _BEACON_IE_OFFSET_);
	if ((p != NULL) && (ielen > 0))
	{
		if ((*(p + 1 + ielen) == 0x2D) && (*(p + 2 + ielen) != 0x2D))
		{
			/* Invalid value 0x2D is detected in Extended Supported Rates (ESR) IE. Try to fix the IE length to avoid failed Beacon parsing. */	
		       	DBG_871X("[WIFIDBG] Error in ESR IE is detected in Beacon of BSSID:"MAC_FMT". Fix the length of ESR IE to avoid failed Beacon parsing.\n", MAC_ARG(GetAddr3Ptr(pframe)));
		       	*(p + 1) = ielen - 1;
		}
	}
#endif

	if (pmlmeext->sitesurvey_res.state == SCAN_PROCESS)
	{
		report_survey_event(padapter, precv_frame);
#ifdef CONFIG_CONCURRENT_MODE
		report_survey_event(padapter->pbuddy_adapter, precv_frame);	
#endif

#ifdef CONFIG_DUALMAC_CONCURRENT
		dc_report_survey_event(padapter, precv_frame);
#endif

		return _SUCCESS;
	}

	if (_rtw_memcmp(GetAddr3Ptr(pframe), get_my_bssid(&pmlmeinfo->network), ETH_ALEN))
	{
		if (pmlmeinfo->state & WIFI_FW_AUTH_NULL)
		{
			//check the vendor of the assoc AP
			pmlmeinfo->assoc_AP_vendor = check_assoc_AP(pframe+sizeof(struct rtw_ieee80211_hdr_3addr), len-sizeof(struct rtw_ieee80211_hdr_3addr));				
#ifdef CONFIG_P2P_PS
			// do P2P PS Before link ? , ToDo
			//process_p2p_ps_ie(padapter, (pframe + WLAN_HDR_A3_LEN), (len - WLAN_HDR_A3_LEN));
#endif // CONFIG_P2P_PS

			//update TSF Value
			update_TSF(pmlmeext, pframe, len);

			//start auth
			start_clnt_auth(padapter);

			return _SUCCESS;
		}

		if(((pmlmeinfo->state&0x03) == WIFI_FW_STATION_STATE) && (pmlmeinfo->state & WIFI_FW_ASSOC_SUCCESS))
		{
			if ((psta = rtw_get_stainfo(pstapriv, GetAddr2Ptr(pframe))) != NULL)
			{
				#ifdef CONFIG_PATCH_JOIN_WRONG_CHANNEL        
				//Merge from 8712 FW code
				if (cmp_pkt_chnl_diff(padapter,pframe,len) != 0)        
				{            // join wrong channel, deauth and reconnect           
					issue_deauth(padapter, (&(pmlmeinfo->network))->MacAddress, WLAN_REASON_DEAUTH_LEAVING);

					report_del_sta_event(padapter,(&(pmlmeinfo->network))->MacAddress, WLAN_REASON_JOIN_WRONG_CHANNEL);    		
					pmlmeinfo->state &= (~WIFI_FW_ASSOC_SUCCESS);    		
					return _SUCCESS;
				}        
				#endif //CONFIG_PATCH_JOIN_WRONG_CHANNEL

				//update WMM, ERP in the beacon
				//todo: the timer is used instead of the number of the beacon received
				if ((sta_rx_pkts(psta) & 0xf) == 0)
				{
					//DBG_871X("update_bcn_info\n");
					update_beacon_info(padapter, pframe, len, psta);
				}
				
#ifdef CONFIG_DFS
				process_csa_ie(padapter, pframe, len);	//channel switch announcement
#endif //CONFIG_DFS

#ifdef CONFIG_P2P_PS
				//if(psta->ieee8021x_blocked == _FALSE) // do not allow P2P PS during EAPOL handshake ?
				process_p2p_ps_ie(padapter, (pframe + WLAN_HDR_A3_LEN), (len - WLAN_HDR_A3_LEN));
#endif //CONFIG_P2P_PS

				#if 0 //move to validate_recv_mgnt_frame
				psta->sta_stats.rx_mgnt_pkts++;
				#endif
			}
		}
		else if((pmlmeinfo->state&0x03) == WIFI_FW_ADHOC_STATE)
		{
			if ((psta = rtw_get_stainfo(pstapriv, GetAddr2Ptr(pframe))) != NULL)
			{
				//update WMM, ERP in the beacon
				//todo: the timer is used instead of the number of the beacon received
				if ((sta_rx_pkts(psta) & 0xf) == 0)
				{
					//DBG_871X("update_bcn_info\n");
					update_beacon_info(padapter, pframe, len, psta);
				}

				#if 0 //move to validate_recv_mgnt_frame
				psta->sta_stats.rx_mgnt_pkts++;
				#endif
			}
			else
			{
				//allocate a new CAM entry for IBSS station
				if ((cam_idx = allocate_fw_sta_entry(padapter)) == NUM_STA)
				{
					goto _END_ONBEACON_;
				}

				//get supported rate
				if (update_sta_support_rate(padapter, (pframe + WLAN_HDR_A3_LEN + _BEACON_IE_OFFSET_), (len - WLAN_HDR_A3_LEN - _BEACON_IE_OFFSET_), cam_idx) == _FAIL)
				{
					pmlmeinfo->FW_sta_info[cam_idx].status = 0;
					goto _END_ONBEACON_;
				}

				//update TSF Value
				update_TSF(pmlmeext, pframe, len);			

				//report sta add event
				report_add_sta_event(padapter, GetAddr2Ptr(pframe), cam_idx);
			}
		}
	}

_END_ONBEACON_:

	return _SUCCESS;

}