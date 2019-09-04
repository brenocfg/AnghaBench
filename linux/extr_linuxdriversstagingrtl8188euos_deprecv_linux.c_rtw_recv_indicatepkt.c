#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sta_priv {int dummy; } ;
struct sta_info {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  protocol; struct net_device* dev; int /*<<< orphan*/  ip_summed; } ;
struct rx_pkt_attrib {int /*<<< orphan*/  dst; } ;
struct __queue {int dummy; } ;
struct recv_priv {struct __queue free_recv_queue; } ;
struct recv_frame {struct sk_buff* pkt; struct rx_pkt_attrib attrib; } ;
struct net_device {int dummy; } ;
struct mlme_priv {int dummy; } ;
struct adapter {struct net_device* pnetdev; int /*<<< orphan*/  eeprompriv; struct sta_priv stapriv; struct recv_priv recvpriv; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WIFI_AP_STATE ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_recv_osdep_c_ ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  myid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  rtw_free_recvframe (struct recv_frame*,struct __queue*) ; 
 struct sta_info* rtw_get_bcmc_stainfo (struct adapter*) ; 
 struct sta_info* rtw_get_stainfo (struct sta_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_recv_select_queue (struct sk_buff*) ; 
 int /*<<< orphan*/  rtw_xmit_entry (struct sk_buff*,struct net_device*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_queue_mapping (struct sk_buff*,int /*<<< orphan*/ ) ; 

int rtw_recv_indicatepkt(struct adapter *padapter,
			 struct recv_frame *precv_frame)
{
	struct recv_priv *precvpriv;
	struct __queue *pfree_recv_queue;
	struct sk_buff *skb;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;

	precvpriv = &(padapter->recvpriv);
	pfree_recv_queue = &(precvpriv->free_recv_queue);

	skb = precv_frame->pkt;
	if (!skb) {
		RT_TRACE(_module_recv_osdep_c_, _drv_err_,
			 ("rtw_recv_indicatepkt():skb == NULL something wrong!!!!\n"));
		goto _recv_indicatepkt_drop;
	}

	if (check_fwstate(pmlmepriv, WIFI_AP_STATE)) {
		struct sk_buff *pskb2 = NULL;
		struct sta_info *psta = NULL;
		struct sta_priv *pstapriv = &padapter->stapriv;
		struct rx_pkt_attrib *pattrib = &precv_frame->attrib;
		bool mcast = is_multicast_ether_addr(pattrib->dst);

		if (memcmp(pattrib->dst, myid(&padapter->eeprompriv),
			   ETH_ALEN)) {
			if (mcast) {
				psta = rtw_get_bcmc_stainfo(padapter);
				pskb2 = skb_clone(skb, GFP_ATOMIC);
			} else {
				psta = rtw_get_stainfo(pstapriv, pattrib->dst);
			}

			if (psta) {
				struct net_device *pnetdev;

				pnetdev = (struct net_device *)padapter->pnetdev;
				skb->dev = pnetdev;
				skb_set_queue_mapping(skb, rtw_recv_select_queue(skb));

				rtw_xmit_entry(skb, pnetdev);

				if (mcast)
					skb = pskb2;
				else
					goto _recv_indicatepkt_end;
			}
		}
	}

	skb->ip_summed = CHECKSUM_NONE;
	skb->dev = padapter->pnetdev;
	skb->protocol = eth_type_trans(skb, padapter->pnetdev);

	netif_rx(skb);

_recv_indicatepkt_end:

	/*  pointers to NULL before rtw_free_recvframe() */
	precv_frame->pkt = NULL;

	rtw_free_recvframe(precv_frame, pfree_recv_queue);

	RT_TRACE(_module_recv_osdep_c_, _drv_info_,
		 ("\n rtw_recv_indicatepkt :after netif_rx!!!!\n"));

	return _SUCCESS;

_recv_indicatepkt_drop:

	 /* enqueue back to free_recv_queue */
	rtw_free_recvframe(precv_frame, pfree_recv_queue);

	return _FAIL;
}