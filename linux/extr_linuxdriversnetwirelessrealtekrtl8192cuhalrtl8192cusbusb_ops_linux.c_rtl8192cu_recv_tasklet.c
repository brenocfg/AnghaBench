#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct recv_priv {int /*<<< orphan*/  rx_skb_queue; } ;
typedef  int /*<<< orphan*/  _pkt ;
struct TYPE_3__ {scalar_t__ bDriverStopped; scalar_t__ bSurpriseRemoved; struct recv_priv recvpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_8192C (char*) ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  recvbuf2recvframe (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_skb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * skb_dequeue (int /*<<< orphan*/ *) ; 

void rtl8192cu_recv_tasklet(void *priv)
{
	_pkt			*pskb;
	_adapter		*padapter = (_adapter*)priv;
	struct recv_priv	*precvpriv = &padapter->recvpriv;
	
	while (NULL != (pskb = skb_dequeue(&precvpriv->rx_skb_queue)))
	{
		if ((padapter->bDriverStopped == _TRUE)||(padapter->bSurpriseRemoved== _TRUE))
		{
			DBG_8192C("recv_tasklet => bDriverStopped or bSurpriseRemoved \n");
			rtw_skb_free(pskb);
			break;
		}
	
		recvbuf2recvframe(padapter, pskb);

#ifdef CONFIG_PREALLOC_RECV_SKB

		skb_reset_tail_pointer(pskb);

		pskb->len = 0;
		
		skb_queue_tail(&precvpriv->free_recv_skb_queue, pskb);
		
#else
		rtw_skb_free(pskb);
#endif
				
	}
	
}