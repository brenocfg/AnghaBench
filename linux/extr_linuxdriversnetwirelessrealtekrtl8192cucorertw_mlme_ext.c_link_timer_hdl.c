#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mlme_ext_info {int state; scalar_t__ reauth_count; int auth_seq; scalar_t__ reassoc_count; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct TYPE_6__ {struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*) ; 
 scalar_t__ REASSOC_LIMIT ; 
 int /*<<< orphan*/  REASSOC_TO ; 
 scalar_t__ REAUTH_LIMIT ; 
 int /*<<< orphan*/  REAUTH_TO ; 
 int WIFI_FW_ASSOC_STATE ; 
 int WIFI_FW_AUTH_NULL ; 
 int WIFI_FW_AUTH_STATE ; 
 void* WIFI_FW_NULL_STATE ; 
 int /*<<< orphan*/  issue_assocreq (TYPE_1__*) ; 
 int /*<<< orphan*/  issue_auth (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report_join_res (TYPE_1__*,int) ; 
 int /*<<< orphan*/  set_link_timer (struct mlme_ext_priv*,int /*<<< orphan*/ ) ; 

void link_timer_hdl(_adapter *padapter)
{
	//static unsigned int		rx_pkt = 0;
	//static u64				tx_cnt = 0;
	//struct xmit_priv		*pxmitpriv = &(padapter->xmitpriv);
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	//struct sta_priv		*pstapriv = &padapter->stapriv;

#ifdef PLATFORM_FREEBSD
	rtw_mtx_lock(NULL);
	 if (callout_pending(&padapter->mlmeextpriv.survey_timer.callout)) {
		 /* callout was reset */
		 //mtx_unlock(&sc->sc_mtx);
		 rtw_mtx_unlock(NULL);
		 return;
	 }
	 if (!callout_active(&padapter->mlmeextpriv.survey_timer.callout)) {
		 /* callout was stopped */
		 //mtx_unlock(&sc->sc_mtx);
		 rtw_mtx_unlock(NULL);
		 return;
	 }
	 callout_deactivate(&padapter->mlmeextpriv.survey_timer.callout);

	
#endif

	if (pmlmeinfo->state & WIFI_FW_AUTH_NULL)
	{
		DBG_871X("link_timer_hdl:no beacon while connecting\n");
		pmlmeinfo->state = WIFI_FW_NULL_STATE;
		report_join_res(padapter, -3);
	}
	else if (pmlmeinfo->state & WIFI_FW_AUTH_STATE)
	{
		//re-auth timer
		if (++pmlmeinfo->reauth_count > REAUTH_LIMIT)
		{
			//if (pmlmeinfo->auth_algo != dot11AuthAlgrthm_Auto)
			//{
				pmlmeinfo->state = 0;
				report_join_res(padapter, -1);
				return;
			//}
			//else
			//{
			//	pmlmeinfo->auth_algo = dot11AuthAlgrthm_Shared;
			//	pmlmeinfo->reauth_count = 0;
			//}
		}
		
		DBG_871X("link_timer_hdl: auth timeout and try again\n");
		pmlmeinfo->auth_seq = 1;
		issue_auth(padapter, NULL, 0);
		set_link_timer(pmlmeext, REAUTH_TO);
	}
	else if (pmlmeinfo->state & WIFI_FW_ASSOC_STATE)
	{
		//re-assoc timer
		if (++pmlmeinfo->reassoc_count > REASSOC_LIMIT)
		{
			pmlmeinfo->state = WIFI_FW_NULL_STATE;
			report_join_res(padapter, -2);
			return;
		}

		DBG_871X("link_timer_hdl: assoc timeout and try again\n");
		issue_assocreq(padapter);
		set_link_timer(pmlmeext, REASSOC_TO);
	}
#if 0
	else if (is_client_associated_to_ap(padapter))
	{
		//linked infrastructure client mode
		if ((psta = rtw_get_stainfo(pstapriv, pmlmeinfo->network.MacAddress)) != NULL)
		{
			/*to monitor whether the AP is alive or not*/
			if (rx_pkt == psta->sta_stats.rx_pkts)
			{
				receive_disconnect(padapter, pmlmeinfo->network.MacAddress);
				return;
			}
			else
			{
				rx_pkt = psta->sta_stats.rx_pkts;
				set_link_timer(pmlmeext, DISCONNECT_TO);
			}

			//update the EDCA paramter according to the Tx/RX mode
			update_EDCA_param(padapter);

			/*to send the AP a nulldata if no frame is xmitted in order to keep alive*/
			if (pmlmeinfo->link_count++ == 0)
			{
				tx_cnt = pxmitpriv->tx_pkts;
			}
			else if ((pmlmeinfo->link_count & 0xf) == 0)
			{
				if (tx_cnt == pxmitpriv->tx_pkts)
				{
					issue_nulldata(padapter, NULL, 0, 0, 0);
				}

				tx_cnt = pxmitpriv->tx_pkts;
			}
		} //end of if ((psta = rtw_get_stainfo(pstapriv, passoc_res->network.MacAddress)) != NULL)
	}
	else if (is_client_associated_to_ibss(padapter))
	{
		//linked IBSS mode
		//for each assoc list entry to check the rx pkt counter
		for (i = IBSS_START_MAC_ID; i < NUM_STA; i++)
		{
			if (pmlmeinfo->FW_sta_info[i].status == 1)
			{
				psta = pmlmeinfo->FW_sta_info[i].psta;

				if (pmlmeinfo->FW_sta_info[i].rx_pkt == psta->sta_stats.rx_pkts)
				{
					pmlmeinfo->FW_sta_info[i].status = 0;
					report_del_sta_event(padapter, psta->hwaddr);
				}
				else
				{
					pmlmeinfo->FW_sta_info[i].rx_pkt = psta->sta_stats.rx_pkts;
				}
			}
		}

		set_link_timer(pmlmeext, DISCONNECT_TO);
	}
#endif

#ifdef PLATFORM_FREEBSD
	rtw_mtx_unlock(NULL);
#endif

	return;
}