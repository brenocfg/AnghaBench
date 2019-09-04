#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct xmit_priv {int free_xmitframe_cnt; scalar_t__ tx_drop; scalar_t__ tx_pkts; } ;
struct mlme_priv {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  os_tx_m2u_stop; int /*<<< orphan*/  os_tx_err_up; int /*<<< orphan*/  os_tx; } ;
struct TYPE_9__ {scalar_t__ wifi_spec; } ;
struct adapter {TYPE_2__ tx_logs; TYPE_1__ registrypriv; struct mlme_priv mlmepriv; struct xmit_priv xmitpriv; } ;
typedef  int s32 ;
struct TYPE_11__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ _pkt ;
typedef  int /*<<< orphan*/  _nic_hdl ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_COUNTER (int /*<<< orphan*/ ) ; 
 scalar_t__ ICMPV6_MCAST_MAC (int /*<<< orphan*/ ) ; 
 scalar_t__ IP_MCAST_MAC (int /*<<< orphan*/ ) ; 
 int NR_XMITFRAME ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WIFI_AP_STATE ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 int /*<<< orphan*/  _module_xmit_osdep_c_ ; 
 int check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (TYPE_3__*) ; 
 int /*<<< orphan*/  rtw_check_xmit_resource (struct adapter*,TYPE_3__*) ; 
 int rtw_if_up (struct adapter*) ; 
 int /*<<< orphan*/  rtw_mc2u_disable ; 
 int rtw_mlcst2unicst (struct adapter*,TYPE_3__*) ; 
 scalar_t__ rtw_netdev_priv (int /*<<< orphan*/ ) ; 
 int rtw_xmit (struct adapter*,TYPE_3__**) ; 

int _rtw_xmit_entry(_pkt *pkt, _nic_hdl pnetdev)
{
	struct adapter *padapter = (struct adapter *)rtw_netdev_priv(pnetdev);
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	s32 res = 0;

	DBG_COUNTER(padapter->tx_logs.os_tx);
	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("+xmit_enry\n"));

	if (rtw_if_up(padapter) == false) {
		DBG_COUNTER(padapter->tx_logs.os_tx_err_up);
		RT_TRACE(_module_xmit_osdep_c_, _drv_err_, ("rtw_xmit_entry: rtw_if_up fail\n"));
		#ifdef DBG_TX_DROP_FRAME
		DBG_871X("DBG_TX_DROP_FRAME %s if_up fail\n", __func__);
		#endif
		goto drop_packet;
	}

	rtw_check_xmit_resource(padapter, pkt);

	if (!rtw_mc2u_disable
		&& check_fwstate(pmlmepriv, WIFI_AP_STATE) == true
		&& (IP_MCAST_MAC(pkt->data)
			|| ICMPV6_MCAST_MAC(pkt->data)
			#ifdef CONFIG_TX_BCAST2UNI
			|| is_broadcast_mac_addr(pkt->data)
			#endif
			)
		&& padapter->registrypriv.wifi_spec == 0) {
		if (pxmitpriv->free_xmitframe_cnt > (NR_XMITFRAME/4)) {
			res = rtw_mlcst2unicst(padapter, pkt);
			if (res == true)
				goto exit;
		} else {
			/* DBG_871X("Stop M2U(%d, %d)! ", pxmitpriv->free_xmitframe_cnt, pxmitpriv->free_xmitbuf_cnt); */
			/* DBG_871X("!m2u); */
			DBG_COUNTER(padapter->tx_logs.os_tx_m2u_stop);
		}
	}

	res = rtw_xmit(padapter, &pkt);
	if (res < 0) {
		#ifdef DBG_TX_DROP_FRAME
		DBG_871X("DBG_TX_DROP_FRAME %s rtw_xmit fail\n", __func__);
		#endif
		goto drop_packet;
	}

	RT_TRACE(_module_xmit_osdep_c_, _drv_info_, ("rtw_xmit_entry: tx_pkts =%d\n", (u32)pxmitpriv->tx_pkts));
	goto exit;

drop_packet:
	pxmitpriv->tx_drop++;
	dev_kfree_skb_any(pkt);
	RT_TRACE(_module_xmit_osdep_c_, _drv_notice_, ("rtw_xmit_entry: drop, tx_drop =%d\n", (u32)pxmitpriv->tx_drop));

exit:
	return 0;
}