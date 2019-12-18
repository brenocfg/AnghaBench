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
typedef  void* u8 ;
struct sk_buff {int dummy; } ;
struct nfc_llcp_ui_cb {void* ssap; void* dsap; } ;
struct TYPE_2__ {scalar_t__ sk_type; } ;
struct nfc_llcp_sock {TYPE_1__ sk; } ;
struct nfc_llcp_local {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLCP_HEADER_SIZE ; 
 int /*<<< orphan*/  LLCP_SAP_SDP ; 
 scalar_t__ SOCK_DGRAM ; 
 void* nfc_llcp_dsap (struct sk_buff*) ; 
 struct nfc_llcp_sock* nfc_llcp_sock_get (struct nfc_llcp_local*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_llcp_sock_put (struct nfc_llcp_sock*) ; 
 void* nfc_llcp_ssap (struct sk_buff*) ; 
 struct nfc_llcp_ui_cb* nfc_llcp_ui_skb_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*,void*,void*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  skb_get (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_queue_rcv_skb (TYPE_1__*,struct sk_buff*) ; 

__attribute__((used)) static void nfc_llcp_recv_ui(struct nfc_llcp_local *local,
			     struct sk_buff *skb)
{
	struct nfc_llcp_sock *llcp_sock;
	struct nfc_llcp_ui_cb *ui_cb;
	u8 dsap, ssap;

	dsap = nfc_llcp_dsap(skb);
	ssap = nfc_llcp_ssap(skb);

	ui_cb = nfc_llcp_ui_skb_cb(skb);
	ui_cb->dsap = dsap;
	ui_cb->ssap = ssap;

	pr_debug("%d %d\n", dsap, ssap);

	/* We're looking for a bound socket, not a client one */
	llcp_sock = nfc_llcp_sock_get(local, dsap, LLCP_SAP_SDP);
	if (llcp_sock == NULL || llcp_sock->sk.sk_type != SOCK_DGRAM)
		return;

	/* There is no sequence with UI frames */
	skb_pull(skb, LLCP_HEADER_SIZE);
	if (!sock_queue_rcv_skb(&llcp_sock->sk, skb)) {
		/*
		 * UI frames will be freed from the socket layer, so we
		 * need to keep them alive until someone receives them.
		 */
		skb_get(skb);
	} else {
		pr_err("Receive queue is full\n");
	}

	nfc_llcp_sock_put(llcp_sock);
}