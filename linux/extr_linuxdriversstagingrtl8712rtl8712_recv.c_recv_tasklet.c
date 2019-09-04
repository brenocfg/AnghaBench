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
struct sk_buff {scalar_t__ len; } ;
struct recv_priv {int /*<<< orphan*/  free_recv_skb_queue; int /*<<< orphan*/  rx_skb_queue; } ;
struct _adapter {struct recv_priv recvpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  recvbuf2recvframe (struct _adapter*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_cloned (struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_tail_pointer (struct sk_buff*) ; 

__attribute__((used)) static void recv_tasklet(void *priv)
{
	struct sk_buff *pskb;
	struct _adapter *padapter = priv;
	struct recv_priv *precvpriv = &padapter->recvpriv;

	while (NULL != (pskb = skb_dequeue(&precvpriv->rx_skb_queue))) {
		recvbuf2recvframe(padapter, pskb);
		skb_reset_tail_pointer(pskb);
		pskb->len = 0;
		if (!skb_cloned(pskb))
			skb_queue_tail(&precvpriv->free_recv_skb_queue, pskb);
		else
			consume_skb(pskb);
	}
}