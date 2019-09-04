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
struct sk_buff {int /*<<< orphan*/ * data; } ;
struct nfc_llcp_sock {int /*<<< orphan*/  recv_n; struct nfc_llcp_local* local; } ;
struct nfc_llcp_local {int /*<<< orphan*/  tx_queue; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  LLCP_PDU_RR ; 
 int /*<<< orphan*/  LLCP_SEQUENCE_SIZE ; 
 struct sk_buff* llcp_allocate_pdu (struct nfc_llcp_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 

int nfc_llcp_send_rr(struct nfc_llcp_sock *sock)
{
	struct sk_buff *skb;
	struct nfc_llcp_local *local;

	pr_debug("Send rr nr %d\n", sock->recv_n);

	local = sock->local;
	if (local == NULL)
		return -ENODEV;

	skb = llcp_allocate_pdu(sock, LLCP_PDU_RR, LLCP_SEQUENCE_SIZE);
	if (skb == NULL)
		return -ENOMEM;

	skb_put(skb, LLCP_SEQUENCE_SIZE);

	skb->data[2] = sock->recv_n;

	skb_queue_head(&local->tx_queue, skb);

	return 0;
}