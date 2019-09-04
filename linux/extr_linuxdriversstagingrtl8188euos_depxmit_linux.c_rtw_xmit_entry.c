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
typedef  int /*<<< orphan*/  u32 ;
struct xmit_priv {int free_xmitframe_cnt; scalar_t__ tx_drop; scalar_t__ tx_pkts; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
struct mlme_priv {int dummy; } ;
struct TYPE_2__ {scalar_t__ wifi_spec; } ;
struct adapter {TYPE_1__ registrypriv; struct mlme_priv mlmepriv; struct xmit_priv xmitpriv; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
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
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  rtw_check_xmit_resource (struct adapter*,struct sk_buff*) ; 
 int rtw_if_up (struct adapter*) ; 
 int /*<<< orphan*/  rtw_mc2u_disable ; 
 scalar_t__ rtw_mlcst2unicst (struct adapter*,struct sk_buff*) ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 
 scalar_t__ rtw_xmit (struct adapter*,struct sk_buff**) ; 

int rtw_xmit_entry(struct sk_buff *pkt, struct  net_device *pnetdev)
{
	struct adapter *padapter = (struct adapter *)rtw_netdev_priv(pnetdev);
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;
	struct mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	s32 res = 0;

	RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("+xmit_enry\n"));

	if (rtw_if_up(padapter) == false) {
		RT_TRACE(_module_xmit_osdep_c_, _drv_err_, ("rtw_xmit_entry: rtw_if_up fail\n"));
		goto drop_packet;
	}

	rtw_check_xmit_resource(padapter, pkt);

	if (!rtw_mc2u_disable && check_fwstate(pmlmepriv, WIFI_AP_STATE) &&
	    (IP_MCAST_MAC(pkt->data) || ICMPV6_MCAST_MAC(pkt->data)) &&
	    (padapter->registrypriv.wifi_spec == 0)) {
		if (pxmitpriv->free_xmitframe_cnt > (NR_XMITFRAME/4)) {
			res = rtw_mlcst2unicst(padapter, pkt);
			if (res)
				goto exit;
		}
	}

	res = rtw_xmit(padapter, &pkt);
	if (res < 0)
		goto drop_packet;

	pxmitpriv->tx_pkts++;
	RT_TRACE(_module_xmit_osdep_c_, _drv_info_, ("rtw_xmit_entry: tx_pkts=%d\n", (u32)pxmitpriv->tx_pkts));
	goto exit;

drop_packet:
	pxmitpriv->tx_drop++;
	dev_kfree_skb_any(pkt);
	RT_TRACE(_module_xmit_osdep_c_, _drv_notice_, ("rtw_xmit_entry: drop, tx_drop=%d\n", (u32)pxmitpriv->tx_drop));

exit:
	return 0;
}