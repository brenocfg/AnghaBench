#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int len; scalar_t__* rx_data; } ;
struct TYPE_10__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
typedef  int uint ;
typedef  scalar_t__ u8 ;
struct TYPE_12__ {scalar_t__ join_res; } ;
struct mlme_priv {TYPE_4__ cur_network; } ;
struct TYPE_11__ {int /*<<< orphan*/  SsidLength; scalar_t__ Ssid; } ;
struct TYPE_14__ {TYPE_3__ Ssid; } ;
struct mlme_ext_info {scalar_t__ hidden_ssid_mode; TYPE_6__ network; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct TYPE_13__ {struct mlme_ext_priv mlmeextpriv; struct mlme_priv mlmepriv; } ;
typedef  TYPE_5__ _adapter ;
typedef  TYPE_6__ WLAN_BSSID_EX ;

/* Variables and functions */
 int WIFI_ADHOC_MASTER_STATE ; 
 int WIFI_AP_STATE ; 
 int WIFI_STATION_STATE ; 
 int WLAN_HDR_A3_LEN ; 
 scalar_t__ _FALSE ; 
 int _FW_LINKED ; 
 int _PROBEREQ_IE_OFFSET_ ; 
 int /*<<< orphan*/  _SSID_IE_ ; 
 unsigned int _SUCCESS ; 
 scalar_t__ _TRUE ; 
 scalar_t__ _rtw_memcmp (void*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int) ; 
 int /*<<< orphan*/  get_sa (scalar_t__*) ; 
 int /*<<< orphan*/  issue_probersp (TYPE_5__*,int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned char* rtw_get_ie (scalar_t__*,int /*<<< orphan*/ ,int*,int) ; 

unsigned int OnProbeReq(_adapter *padapter, union recv_frame *precv_frame)
{
	unsigned int	ielen;
	unsigned char	*p;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	WLAN_BSSID_EX 	*cur = &(pmlmeinfo->network);
	u8 *pframe = precv_frame->u.hdr.rx_data;
	uint len = precv_frame->u.hdr.len;
	u8 is_valid_p2p_probereq = _FALSE;

#ifdef CONFIG_P2P
	struct wifidirect_info	*pwdinfo = &(padapter->wdinfo);
	struct rx_pkt_attrib	*pattrib = &precv_frame->u.hdr.attrib;
	u8 wifi_test_chk_rate = 1;
	
	if (	!rtw_p2p_chk_state(pwdinfo, P2P_STATE_NONE) && 
		!rtw_p2p_chk_state(pwdinfo, P2P_STATE_IDLE) && 
		!rtw_p2p_chk_role(pwdinfo, P2P_ROLE_CLIENT) &&
		!rtw_p2p_chk_state(pwdinfo, P2P_STATE_FIND_PHASE_SEARCH) &&
		!rtw_p2p_chk_state(pwdinfo, P2P_STATE_SCAN)
	   )
	{
		//	Commented by Albert 2011/03/17
		//	mcs_rate = 0 -> CCK 1M rate
		//	mcs_rate = 1 -> CCK 2M rate
		//	mcs_rate = 2 -> CCK 5.5M rate
		//	mcs_rate = 3 -> CCK 11M rate
		//	In the P2P mode, the driver should not support the CCK rate

		//	Commented by Kurt 2012/10/16
		//	IOT issue: Google Nexus7 use 1M rate to send p2p_probe_req after GO nego completed and Nexus7 is client
#ifdef CONFIG_WIFI_TEST
		if ( pattrib->mcs_rate <= 3 )
		{
			wifi_test_chk_rate = 0;
		}
#endif //CONFIG_WIFI_TEST

		if( wifi_test_chk_rate == 1 )
		{
			if((is_valid_p2p_probereq = process_probe_req_p2p_ie(pwdinfo, pframe, len)) == _TRUE)
			{
				if(rtw_p2p_chk_role(pwdinfo, P2P_ROLE_DEVICE))
				{
					p2p_listen_state_process( padapter,  get_sa(pframe));

					return _SUCCESS;	
				}

				if(rtw_p2p_chk_role(pwdinfo, P2P_ROLE_GO))
				{
					goto _continue;
				}
			}
		}
	}

_continue:
#endif //CONFIG_P2P

	if(check_fwstate(pmlmepriv, WIFI_STATION_STATE))
	{
		return _SUCCESS;
	}

	if(check_fwstate(pmlmepriv, _FW_LINKED) == _FALSE && 
		check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE|WIFI_AP_STATE)==_FALSE)
	{
		return _SUCCESS;
	}


	//DBG_871X("+OnProbeReq\n");

#ifdef CONFIG_AUTO_AP_MODE
	if(check_fwstate(pmlmepriv, _FW_LINKED) == _TRUE &&
			pmlmepriv->cur_network.join_res == _TRUE)
	{
		_irqL	irqL;
		struct sta_info	*psta;
		u8 *mac_addr, *peer_addr;
		struct sta_priv *pstapriv = &padapter->stapriv;
		u8 RC_OUI[4]={0x00,0xE0,0x4C,0x0A};
		//EID[1] + EID_LEN[1] + RC_OUI[4] + MAC[6] + PairingID[2] + ChannelNum[2]

		p = rtw_get_ie(pframe + WLAN_HDR_A3_LEN + _PROBEREQ_IE_OFFSET_, _VENDOR_SPECIFIC_IE_, (int *)&ielen,
			len - WLAN_HDR_A3_LEN - _PROBEREQ_IE_OFFSET_);

		if(!p || ielen !=14)
			goto _non_rc_device;

		if(!_rtw_memcmp(p+2, RC_OUI, sizeof(RC_OUI)))
			goto _non_rc_device;

		if(!_rtw_memcmp(p+6, get_sa(pframe), ETH_ALEN))
		{
			DBG_871X("%s, do rc pairing ("MAC_FMT"), but mac addr mismatch!("MAC_FMT")\n", __FUNCTION__,
				MAC_ARG(get_sa(pframe)), MAC_ARG(p+6));

			goto _non_rc_device;
		}

		DBG_871X("%s, got the pairing device("MAC_FMT")\n", __FUNCTION__,  MAC_ARG(get_sa(pframe)));

		//new a station
		psta = rtw_get_stainfo(pstapriv, get_sa(pframe));
		if (psta == NULL)
		{
			// allocate a new one
			DBG_871X("going to alloc stainfo for rc="MAC_FMT"\n",  MAC_ARG(get_sa(pframe)));
			psta = rtw_alloc_stainfo(pstapriv, get_sa(pframe));
			if (psta == NULL)
			{
				//TODO:
				DBG_871X(" Exceed the upper limit of supported clients...\n");
				return _SUCCESS;
			}

			_enter_critical_bh(&pstapriv->asoc_list_lock, &irqL);
			if (rtw_is_list_empty(&psta->asoc_list))
			{
				psta->expire_to = pstapriv->expire_to;
				rtw_list_insert_tail(&psta->asoc_list, &pstapriv->asoc_list);
				pstapriv->asoc_list_cnt++;
			}
			_exit_critical_bh(&pstapriv->asoc_list_lock, &irqL);

			//generate pairing ID
			mac_addr = myid(&(padapter->eeprompriv));
			peer_addr = psta->hwaddr;
			psta->pid = (u16)(((mac_addr[4]<<8) + mac_addr[5]) + ((peer_addr[4]<<8) + peer_addr[5]));

			//update peer stainfo
			psta->isrc = _TRUE;
			//psta->aid = 0;
			//psta->mac_id = 2;

			/* get a unique AID */
			if (psta->aid > 0) {
				DBG_871X("old AID %d\n", psta->aid);
			} else {
				for (psta->aid = 1; psta->aid <= NUM_STA; psta->aid++)
					if (pstapriv->sta_aid[psta->aid - 1] == NULL)
						break;

				if (psta->aid > pstapriv->max_num_sta) {
					psta->aid = 0;
					DBG_871X("no room for more AIDs\n");
					return _SUCCESS;
				} else {
					pstapriv->sta_aid[psta->aid - 1] = psta;
					DBG_871X("allocate new AID = (%d)\n", psta->aid);
				}
			}
			
			psta->qos_option = 1;
			psta->htpriv.ht_option = _TRUE;
			psta->ieee8021x_blocked = _FALSE;
			psta->htpriv.ampdu_enable = _FALSE;
			psta->htpriv.sgi = _FALSE;
			psta->htpriv.bwmode = HT_CHANNEL_WIDTH_20;
			psta->htpriv.ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;

			//rtw_hal_set_odm_var(padapter, HAL_ODM_STA_INFO, psta, _TRUE);

			psta->htpriv.agg_enable_bitmap = 0x0;//reset
			psta->htpriv.candidate_tid_bitmap = 0x0;//reset

			_rtw_memset((void*)&psta->sta_stats, 0, sizeof(struct stainfo_stats));

			_enter_critical_bh(&psta->lock, &irqL);
			psta->state |= _FW_LINKED;
			_exit_critical_bh(&psta->lock, &irqL);

			report_add_sta_event(padapter, psta->hwaddr, psta->aid);

		}

		issue_probersp(padapter, get_sa(pframe), _FALSE);

		return _SUCCESS;

	}

_non_rc_device:

	return _SUCCESS;
#endif //CONFIG_AUTO_AP_MODE


#ifdef CONFIG_CONCURRENT_MODE
	if(((pmlmeinfo->state&0x03) == WIFI_FW_AP_STATE) &&
		check_buddy_fwstate(padapter, _FW_UNDER_LINKING|_FW_UNDER_SURVEY))
	{
		//don't process probe req
		return _SUCCESS;
	}
#endif		

	p = rtw_get_ie(pframe + WLAN_HDR_A3_LEN + _PROBEREQ_IE_OFFSET_, _SSID_IE_, (int *)&ielen,
			len - WLAN_HDR_A3_LEN - _PROBEREQ_IE_OFFSET_);


	//check (wildcard) SSID 
	if (p != NULL)
	{
		if(is_valid_p2p_probereq == _TRUE)
		{
			goto _issue_probersp;
		}

		if ( (ielen != 0 && _FALSE ==_rtw_memcmp((void *)(p+2), (void *)cur->Ssid.Ssid, cur->Ssid.SsidLength))
			|| (ielen == 0 && pmlmeinfo->hidden_ssid_mode)
		)
		{
			return _SUCCESS;
		}

_issue_probersp:

		if(check_fwstate(pmlmepriv, _FW_LINKED) == _TRUE && 
			pmlmepriv->cur_network.join_res == _TRUE)
		{
			//DBG_871X("+issue_probersp during ap mode\n");
			issue_probersp(padapter, get_sa(pframe), is_valid_p2p_probereq);		
		}

	}

	return _SUCCESS;

}