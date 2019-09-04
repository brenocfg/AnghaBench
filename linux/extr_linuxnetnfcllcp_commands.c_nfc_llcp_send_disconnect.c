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
struct nfc_llcp_sock {struct nfc_dev* dev; struct nfc_llcp_local* local; } ;
struct nfc_llcp_local {int /*<<< orphan*/  tx_queue; } ;
struct nfc_dev {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  LLCP_PDU_DISC ; 
 struct sk_buff* llcp_allocate_pdu (struct nfc_llcp_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

int nfc_llcp_send_disconnect(struct nfc_llcp_sock *sock)
{
	struct sk_buff *skb;
	struct nfc_dev *dev;
	struct nfc_llcp_local *local;

	pr_debug("Sending DISC\n");

	local = sock->local;
	if (local == NULL)
		return -ENODEV;

	dev = sock->dev;
	if (dev == NULL)
		return -ENODEV;

	skb = llcp_allocate_pdu(sock, LLCP_PDU_DISC, 0);
	if (skb == NULL)
		return -ENOMEM;

	skb_queue_tail(&local->tx_queue, skb);

	return 0;
}