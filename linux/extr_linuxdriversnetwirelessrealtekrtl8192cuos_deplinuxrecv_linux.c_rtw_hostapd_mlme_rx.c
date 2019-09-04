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
typedef  union recv_frame {int dummy; } recv_frame ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */

void rtw_hostapd_mlme_rx(_adapter *padapter, union recv_frame *precv_frame)
{
#ifdef CONFIG_HOSTAPD_MLME
	_pkt *skb;
	struct hostapd_priv *phostapdpriv  = padapter->phostapdpriv;
	struct net_device *pmgnt_netdev = phostapdpriv->pmgnt_netdev;

	RT_TRACE(_module_recv_osdep_c_, _drv_info_, ("+rtw_hostapd_mlme_rx\n"));

	skb = precv_frame->u.hdr.pkt;

	if (skb == NULL)
		return;

	skb->data = precv_frame->u.hdr.rx_data;
	skb->tail = precv_frame->u.hdr.rx_tail;
	skb->len = precv_frame->u.hdr.len;

	//pskb_copy = rtw_skb_copy(skb);
//	if(skb == NULL) goto _exit;

	skb->dev = pmgnt_netdev;
	skb->ip_summed = CHECKSUM_NONE;
	skb->pkt_type = PACKET_OTHERHOST;
	//skb->protocol = __constant_htons(0x0019); /*ETH_P_80211_RAW*/
	skb->protocol = __constant_htons(0x0003); /*ETH_P_80211_RAW*/

	//DBG_871X("(1)data=0x%x, head=0x%x, tail=0x%x, mac_header=0x%x, len=%d\n", skb->data, skb->head, skb->tail, skb->mac_header, skb->len);

	//skb->mac.raw = skb->data;
	skb_reset_mac_header(skb);

       //skb_pull(skb, 24);
       _rtw_memset(skb->cb, 0, sizeof(skb->cb));

	rtw_netif_rx(pmgnt_netdev, skb);

	precv_frame->u.hdr.pkt = NULL; // set pointer to NULL before rtw_free_recvframe() if call rtw_netif_rx()
#endif
}