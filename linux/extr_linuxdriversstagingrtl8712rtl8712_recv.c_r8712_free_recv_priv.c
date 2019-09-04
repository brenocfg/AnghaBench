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
struct recv_priv {int /*<<< orphan*/  free_recv_skb_queue; int /*<<< orphan*/  rx_skb_queue; int /*<<< orphan*/  pallocated_recv_buf; scalar_t__ precv_buf; struct _adapter* adapter; } ;
struct recv_buf {int dummy; } ;
struct _adapter {int /*<<< orphan*/  pnetdev; } ;

/* Variables and functions */
 int NR_RECVBUFF ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  r8712_os_recvbuf_resource_free (struct _adapter*,struct recv_buf*) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

void r8712_free_recv_priv(struct recv_priv *precvpriv)
{
	int i;
	struct recv_buf *precvbuf;
	struct _adapter *padapter = precvpriv->adapter;

	precvbuf = (struct recv_buf *)precvpriv->precv_buf;
	for (i = 0; i < NR_RECVBUFF; i++) {
		r8712_os_recvbuf_resource_free(padapter, precvbuf);
		precvbuf++;
	}
	kfree(precvpriv->pallocated_recv_buf);
	skb_queue_purge(&precvpriv->rx_skb_queue);
	if (skb_queue_len(&precvpriv->rx_skb_queue))
		netdev_warn(padapter->pnetdev, "r8712u: rx_skb_queue not empty\n");
	skb_queue_purge(&precvpriv->free_recv_skb_queue);
	if (skb_queue_len(&precvpriv->free_recv_skb_queue))
		netdev_warn(padapter->pnetdev, "r8712u: free_recv_skb_queue not empty %d\n",
			    skb_queue_len(&precvpriv->free_recv_skb_queue));
}