#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * rx_data; } ;
struct TYPE_8__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  u8 ;
struct sta_priv {int dummy; } ;
struct sta_info {int dummy; } ;
struct TYPE_9__ {scalar_t__ state; } ;
struct mlme_ext_info {int dummy; } ;
struct mlme_ext_priv {TYPE_3__ sitesurvey_res; struct mlme_ext_info mlmext_info; } ;
struct TYPE_10__ {struct sta_priv stapriv; struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_4__ _adapter ;

/* Variables and functions */
 scalar_t__ SCAN_PROCESS ; 
 unsigned int _SUCCESS ; 
 int /*<<< orphan*/  report_survey_event (TYPE_4__*,union recv_frame*) ; 

unsigned int OnProbeRsp(_adapter *padapter, union recv_frame *precv_frame)
{
	struct sta_info		*psta;
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	struct sta_priv		*pstapriv = &padapter->stapriv;
	u8	*pframe = precv_frame->u.hdr.rx_data;
#ifdef CONFIG_P2P
	struct wifidirect_info	*pwdinfo = &padapter->wdinfo;
#endif


#ifdef CONFIG_P2P
	if(rtw_p2p_chk_state(pwdinfo, P2P_STATE_TX_PROVISION_DIS_REQ))
	{
		if ( _TRUE == pwdinfo->tx_prov_disc_info.benable )
		{
			if( _rtw_memcmp( pwdinfo->tx_prov_disc_info.peerIFAddr, GetAddr2Ptr(pframe), ETH_ALEN ) )
			{
				if(rtw_p2p_chk_role(pwdinfo, P2P_ROLE_CLIENT))
				{
					pwdinfo->tx_prov_disc_info.benable = _FALSE;
					issue_p2p_provision_request( padapter,
												pwdinfo->tx_prov_disc_info.ssid.Ssid, 
												pwdinfo->tx_prov_disc_info.ssid.SsidLength,
												pwdinfo->tx_prov_disc_info.peerDevAddr );
				}
				else if ( rtw_p2p_chk_role(pwdinfo, P2P_ROLE_DEVICE) || rtw_p2p_chk_role(pwdinfo, P2P_ROLE_GO) )
				{
					pwdinfo->tx_prov_disc_info.benable = _FALSE;
					issue_p2p_provision_request( padapter,
												NULL, 
												0,
												pwdinfo->tx_prov_disc_info.peerDevAddr );
				}
			}		
		}
		return _SUCCESS;
	}
	else if(rtw_p2p_chk_state(pwdinfo, P2P_STATE_GONEGO_ING))
	{
		if ( _TRUE == pwdinfo->nego_req_info.benable )
		{
			DBG_871X( "[%s] P2P State is GONEGO ING!\n", __FUNCTION__ );
			if( _rtw_memcmp( pwdinfo->nego_req_info.peerDevAddr, GetAddr2Ptr(pframe), ETH_ALEN ) )
			{
				pwdinfo->nego_req_info.benable = _FALSE;
				issue_p2p_GO_request( padapter, pwdinfo->nego_req_info.peerDevAddr);
			}
		}
	}
	else if( rtw_p2p_chk_state(pwdinfo, P2P_STATE_TX_INVITE_REQ ) )
	{
		if ( _TRUE == pwdinfo->invitereq_info.benable )
		{
			DBG_871X( "[%s] P2P_STATE_TX_INVITE_REQ!\n", __FUNCTION__ );
			if( _rtw_memcmp( pwdinfo->invitereq_info.peer_macaddr, GetAddr2Ptr(pframe), ETH_ALEN ) )
			{
				pwdinfo->invitereq_info.benable = _FALSE;
				issue_p2p_invitation_request( padapter, pwdinfo->invitereq_info.peer_macaddr );
			}
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

	#if 0 //move to validate_recv_mgnt_frame
	if (_rtw_memcmp(GetAddr3Ptr(pframe), get_my_bssid(&pmlmeinfo->network), ETH_ALEN))
	{
		if (pmlmeinfo->state & WIFI_FW_ASSOC_SUCCESS)
		{
			if ((psta = rtw_get_stainfo(pstapriv, GetAddr2Ptr(pframe))) != NULL)
			{
				psta->sta_stats.rx_mgnt_pkts++;
			}
		}
	}
	#endif
	
	return _SUCCESS;
	
}