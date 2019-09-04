#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct rx_pkt_attrib {int amsdu; } ;
struct TYPE_12__ {struct rx_pkt_attrib attrib; } ;
struct TYPE_13__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
struct recv_priv {int /*<<< orphan*/  rx_drop; int /*<<< orphan*/  free_recv_queue; } ;
typedef  int /*<<< orphan*/  _queue ;
struct TYPE_14__ {scalar_t__ bDriverStopped; scalar_t__ bSurpriseRemoved; struct recv_priv recvpriv; } ;
typedef  TYPE_3__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  LED_CTL_RX ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int _FAIL ; 
 scalar_t__ _FALSE ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _drv_alert_ ; 
 int /*<<< orphan*/  _drv_debug_ ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 
 int amsdu_to_msdu (TYPE_3__*,union recv_frame*) ; 
 int /*<<< orphan*/  count_rx_stats (TYPE_3__*,union recv_frame*,int /*<<< orphan*/ *) ; 
 union recv_frame* decryptor (TYPE_3__*,union recv_frame*) ; 
 union recv_frame* portctrl (TYPE_3__*,union recv_frame*) ; 
 union recv_frame* recvframe_chk_defrag (TYPE_3__*,union recv_frame*) ; 
 int /*<<< orphan*/  rtw_free_recvframe (union recv_frame*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_led_control (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int rtw_recv_indicatepkt (TYPE_3__*,union recv_frame*) ; 
 int wlanhdr_to_ethhdr (union recv_frame*) ; 

__attribute__((used)) static int recv_func_posthandle(_adapter *padapter, union recv_frame *prframe)
{
	int ret = _SUCCESS;
	union recv_frame *orig_prframe = prframe;
	struct rx_pkt_attrib *pattrib = &prframe->u.hdr.attrib;
	struct recv_priv *precvpriv = &padapter->recvpriv;
	_queue *pfree_recv_queue = &padapter->recvpriv.free_recv_queue;
	
#ifdef CONFIG_MP_INCLUDED
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
#endif //CONFIG_MP_INCLUDED

#ifdef CONFIG_TDLS
	u8 *psnap_type, *pcategory;
	struct sta_info *ptdls_sta = NULL;
#endif //CONFIG_TDLS


	// DATA FRAME
	rtw_led_control(padapter, LED_CTL_RX);

	prframe = decryptor(padapter, prframe);
	if (prframe == NULL) {
		RT_TRACE(_module_rtl871x_recv_c_,_drv_err_,("decryptor: drop pkt\n"));
		#ifdef DBG_RX_DROP_FRAME
		DBG_871X("DBG_RX_DROP_FRAME %s decryptor: drop pkt\n", __FUNCTION__);
		#endif
		ret = _FAIL;
		goto _recv_data_drop;
	}

#if 0
	if ( padapter->adapter_type == PRIMARY_ADAPTER )
	{
		DBG_871X("+++\n");
		{
			int i;
			u8	*ptr = get_recvframe_data(prframe);
			for(i=0; i<140;i=i+8)
				DBG_871X("%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:", *(ptr+i),
				*(ptr+i+1), *(ptr+i+2) ,*(ptr+i+3) ,*(ptr+i+4),*(ptr+i+5), *(ptr+i+6), *(ptr+i+7));

		}
		DBG_871X("---\n");
	}
#endif //RTK_DMP_PLATFORM

#ifdef CONFIG_TDLS
	//check TDLS frame
	psnap_type = get_recvframe_data(orig_prframe);
	psnap_type+=pattrib->hdrlen + pattrib->iv_len+SNAP_SIZE;
	pcategory = psnap_type + ETH_TYPE_LEN + PAYLOAD_TYPE_LEN;

	if((_rtw_memcmp(psnap_type, SNAP_ETH_TYPE_TDLS, ETH_TYPE_LEN)) &&
		((*pcategory==RTW_WLAN_CATEGORY_TDLS) || (*pcategory==RTW_WLAN_CATEGORY_P2P))){
		ret = OnTDLS(padapter, prframe);	//all of functions will return _FAIL
		goto _exit_recv_func;
	}
#endif //CONFIG_TDLS

	prframe = recvframe_chk_defrag(padapter, prframe);
	if(prframe==NULL)	{
		RT_TRACE(_module_rtl871x_recv_c_,_drv_err_,("recvframe_chk_defrag: drop pkt\n"));
		#ifdef DBG_RX_DROP_FRAME
		DBG_871X("DBG_RX_DROP_FRAME %s recvframe_chk_defrag: drop pkt\n", __FUNCTION__);
		#endif
		goto _recv_data_drop;		
	}

	prframe=portctrl(padapter, prframe);
	if (prframe == NULL) {
		RT_TRACE(_module_rtl871x_recv_c_,_drv_err_,("portctrl: drop pkt \n"));
		#ifdef DBG_RX_DROP_FRAME
		DBG_871X("DBG_RX_DROP_FRAME %s portctrl: drop pkt\n", __FUNCTION__);
		#endif
		ret = _FAIL;
		goto _recv_data_drop;
	}

#ifdef CONFIG_TDLS
	if(padapter->tdlsinfo.setup_state == TDLS_LINKED_STATE)
		ptdls_sta = rtw_get_stainfo(&padapter->stapriv, pattrib->src);
	count_rx_stats(padapter, prframe, ptdls_sta);
#else
	count_rx_stats(padapter, prframe, NULL);
#endif //CONFIG_TDLS

#ifdef CONFIG_80211N_HT

	ret = process_recv_indicatepkts(padapter, prframe);
	if (ret != _SUCCESS)
	{
		RT_TRACE(_module_rtl871x_recv_c_,_drv_err_,("recv_func: process_recv_indicatepkts fail! \n"));
		#ifdef DBG_RX_DROP_FRAME
		DBG_871X("DBG_RX_DROP_FRAME %s recv_func: process_recv_indicatepkts fail!\n", __FUNCTION__);
		#endif
		rtw_free_recvframe(orig_prframe, pfree_recv_queue);//free this recv_frame
		goto _recv_data_drop;
	}

#else // CONFIG_80211N_HT

	if (!pattrib->amsdu)
	{
		ret = wlanhdr_to_ethhdr (prframe);
		if (ret != _SUCCESS)
		{
			RT_TRACE(_module_rtl871x_recv_c_,_drv_err_,("wlanhdr_to_ethhdr: drop pkt \n"));
			#ifdef DBG_RX_DROP_FRAME
			DBG_871X("DBG_RX_DROP_FRAME %s wlanhdr_to_ethhdr: drop pkt\n", __FUNCTION__);
			#endif
			rtw_free_recvframe(orig_prframe, pfree_recv_queue);//free this recv_frame
			goto _recv_data_drop;
		}

		if ((padapter->bDriverStopped == _FALSE) && (padapter->bSurpriseRemoved == _FALSE))
		{
			RT_TRACE(_module_rtl871x_recv_c_, _drv_alert_, ("@@@@ recv_func: recv_func rtw_recv_indicatepkt\n" ));
			//indicate this recv_frame
			ret = rtw_recv_indicatepkt(padapter, prframe);
			if (ret != _SUCCESS)
			{	
				#ifdef DBG_RX_DROP_FRAME
				DBG_871X("DBG_RX_DROP_FRAME %s rtw_recv_indicatepkt fail!\n", __FUNCTION__);
				#endif
				goto _recv_data_drop;
			}
		}
		else
		{
			RT_TRACE(_module_rtl871x_recv_c_, _drv_alert_, ("@@@@  recv_func: rtw_free_recvframe\n" ));
			RT_TRACE(_module_rtl871x_recv_c_, _drv_debug_, ("recv_func:bDriverStopped(%d) OR bSurpriseRemoved(%d)", padapter->bDriverStopped, padapter->bSurpriseRemoved));
			#ifdef DBG_RX_DROP_FRAME
			DBG_871X("DBG_RX_DROP_FRAME %s ecv_func:bDriverStopped(%d) OR bSurpriseRemoved(%d)\n", __FUNCTION__,
				padapter->bDriverStopped, padapter->bSurpriseRemoved);
			#endif
			ret = _FAIL;
			rtw_free_recvframe(orig_prframe, pfree_recv_queue); //free this recv_frame
		}

	}
	else if(pattrib->amsdu==1)
	{

		ret = amsdu_to_msdu(padapter, prframe);
		if(ret != _SUCCESS)
		{
			#ifdef DBG_RX_DROP_FRAME
			DBG_871X("DBG_RX_DROP_FRAME %s amsdu_to_msdu fail\n", __FUNCTION__);
			#endif
			rtw_free_recvframe(orig_prframe, pfree_recv_queue);
			goto _recv_data_drop;
		}
	}
	else
	{
		#ifdef DBG_RX_DROP_FRAME
		DBG_871X("DBG_RX_DROP_FRAME %s what is this condition??\n", __FUNCTION__);
		#endif
		goto _recv_data_drop;
	}
#endif // CONFIG_80211N_HT

_exit_recv_func:
	return ret;

_recv_data_drop:
	precvpriv->rx_drop++;
	return ret;
}