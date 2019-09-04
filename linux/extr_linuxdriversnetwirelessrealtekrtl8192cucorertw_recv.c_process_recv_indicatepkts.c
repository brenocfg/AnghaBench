#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union recv_frame {int dummy; } recv_frame ;
struct mlme_priv {int dummy; } ;
struct TYPE_4__ {scalar_t__ bDriverStopped; scalar_t__ bSurpriseRemoved; struct mlme_priv mlmepriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int _FAIL ; 
 scalar_t__ _FALSE ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 
 int /*<<< orphan*/  rtw_recv_indicatepkt (TYPE_1__*,union recv_frame*) ; 
 int wlanhdr_to_ethhdr (union recv_frame*) ; 

int process_recv_indicatepkts(_adapter *padapter, union recv_frame *prframe)
{
	int retval = _SUCCESS;
	//struct recv_priv *precvpriv = &padapter->recvpriv;
	//struct rx_pkt_attrib *pattrib = &prframe->u.hdr.attrib;
	struct mlme_priv	*pmlmepriv = &padapter->mlmepriv;
#ifdef CONFIG_TDLS
	struct sta_info *psta = prframe->u.hdr.psta;
#endif //CONFIG_TDLS

#ifdef CONFIG_80211N_HT

	struct ht_priv	*phtpriv = &pmlmepriv->htpriv;

#ifdef CONFIG_TDLS
	if( (phtpriv->ht_option==_TRUE) ||
		((psta->tdls_sta_state & TDLS_LINKED_STATE) && 
		 (psta->htpriv.ht_option==_TRUE) &&
		 (psta->htpriv.ampdu_enable==_TRUE))) //B/G/N Mode
#else
	if(phtpriv->ht_option==_TRUE)  //B/G/N Mode
#endif //CONFIG_TDLS
	{
		//prframe->u.hdr.preorder_ctrl = &precvpriv->recvreorder_ctrl[pattrib->priority];

		if(recv_indicatepkt_reorder(padapter, prframe)!=_SUCCESS)// including perform A-MPDU Rx Ordering Buffer Control
		{
			#ifdef DBG_RX_DROP_FRAME
			DBG_871X("DBG_RX_DROP_FRAME %s recv_indicatepkt_reorder error!\n", __FUNCTION__);
			#endif
		
			if ((padapter->bDriverStopped == _FALSE) &&
			    (padapter->bSurpriseRemoved == _FALSE))
			{
				retval = _FAIL;
				return retval;
			}
		}
	}
	else //B/G mode
#endif
	{
		retval=wlanhdr_to_ethhdr (prframe);
		if(retval != _SUCCESS)
		{
			RT_TRACE(_module_rtl871x_recv_c_,_drv_err_,("wlanhdr_to_ethhdr: drop pkt \n"));
			#ifdef DBG_RX_DROP_FRAME
			DBG_871X("DBG_RX_DROP_FRAME %s wlanhdr_to_ethhdr error!\n", __FUNCTION__);
			#endif
			return retval;
		}

		if ((padapter->bDriverStopped ==_FALSE)&&( padapter->bSurpriseRemoved==_FALSE))
		{
			//indicate this recv_frame
			RT_TRACE(_module_rtl871x_recv_c_, _drv_notice_, ("@@@@ process_recv_indicatepkts- recv_func recv_indicatepkt\n" ));
			rtw_recv_indicatepkt(padapter, prframe);


		}
		else
		{
			RT_TRACE(_module_rtl871x_recv_c_, _drv_notice_, ("@@@@ process_recv_indicatepkts- recv_func free_indicatepkt\n" ));

			RT_TRACE(_module_rtl871x_recv_c_, _drv_notice_, ("recv_func:bDriverStopped(%d) OR bSurpriseRemoved(%d)", padapter->bDriverStopped, padapter->bSurpriseRemoved));
			retval = _FAIL;
			return retval;
		}

	}

	return retval;

}