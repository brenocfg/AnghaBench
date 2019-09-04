#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct rx_pkt_attrib {int tcpchk_valid; int tcp_chkrpt; } ;
struct TYPE_7__ {TYPE_3__* pkt; int /*<<< orphan*/  len; int /*<<< orphan*/  rx_data; struct rx_pkt_attrib attrib; } ;
struct TYPE_8__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
struct __queue {int dummy; } ;
struct recv_priv {int /*<<< orphan*/  rx_drop; struct __queue free_recv_queue; } ;
struct _adapter {int /*<<< orphan*/  pnetdev; struct recv_priv recvpriv; } ;
struct TYPE_9__ {int /*<<< orphan*/  protocol; int /*<<< orphan*/  dev; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ _pkt ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  eth_type_trans (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_rx (TYPE_3__*) ; 
 int /*<<< orphan*/  r8712_free_recvframe (union recv_frame*,struct __queue*) ; 
 int /*<<< orphan*/  skb_set_tail_pointer (TYPE_3__*,int /*<<< orphan*/ ) ; 

void r8712_recv_indicatepkt(struct _adapter *padapter,
			    union recv_frame *precv_frame)
{
	struct recv_priv *precvpriv;
	struct  __queue	*pfree_recv_queue;
	_pkt *skb;
	struct rx_pkt_attrib *pattrib = &precv_frame->u.hdr.attrib;

	precvpriv = &padapter->recvpriv;
	pfree_recv_queue = &precvpriv->free_recv_queue;
	skb = precv_frame->u.hdr.pkt;
	if (!skb)
		goto _recv_indicatepkt_drop;
	skb->data = precv_frame->u.hdr.rx_data;
	skb->len = precv_frame->u.hdr.len;
	skb_set_tail_pointer(skb, skb->len);
	if ((pattrib->tcpchk_valid == 1) && (pattrib->tcp_chkrpt == 1))
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	else
		skb->ip_summed = CHECKSUM_NONE;
	skb->dev = padapter->pnetdev;
	skb->protocol = eth_type_trans(skb, padapter->pnetdev);
	netif_rx(skb);
	precv_frame->u.hdr.pkt = NULL; /* pointers to NULL before
					* r8712_free_recvframe()
					*/
	r8712_free_recvframe(precv_frame, pfree_recv_queue);
	return;
_recv_indicatepkt_drop:
	 /*enqueue back to free_recv_queue*/
	if (precv_frame)
		r8712_free_recvframe(precv_frame, pfree_recv_queue);
	precvpriv->rx_drop++;
}