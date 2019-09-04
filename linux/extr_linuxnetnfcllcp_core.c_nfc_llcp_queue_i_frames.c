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
struct sk_buff {int dummy; } ;
struct nfc_llcp_sock {scalar_t__ remote_rw; int /*<<< orphan*/  tx_queue; int /*<<< orphan*/  tx_pending_queue; scalar_t__ remote_ready; struct nfc_llcp_local* local; } ;
struct nfc_llcp_local {int /*<<< orphan*/  tx_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfc_llcp_set_nrns (struct nfc_llcp_sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,scalar_t__,scalar_t__) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

int nfc_llcp_queue_i_frames(struct nfc_llcp_sock *sock)
{
	int nr_frames = 0;
	struct nfc_llcp_local *local = sock->local;

	pr_debug("Remote ready %d tx queue len %d remote rw %d",
		 sock->remote_ready, skb_queue_len(&sock->tx_pending_queue),
		 sock->remote_rw);

	/* Try to queue some I frames for transmission */
	while (sock->remote_ready &&
	       skb_queue_len(&sock->tx_pending_queue) < sock->remote_rw) {
		struct sk_buff *pdu;

		pdu = skb_dequeue(&sock->tx_queue);
		if (pdu == NULL)
			break;

		/* Update N(S)/N(R) */
		nfc_llcp_set_nrns(sock, pdu);

		skb_queue_tail(&local->tx_queue, pdu);
		nr_frames++;
	}

	return nr_frames;
}