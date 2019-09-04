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
typedef  int /*<<< orphan*/  u8 ;
struct sock {int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_state; } ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/ * data; } ;
struct nfc_llcp_sock {int /*<<< orphan*/  dsap; struct sock sk; } ;
struct nfc_llcp_local {int /*<<< orphan*/  sockets; int /*<<< orphan*/  connecting_sockets; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLCP_CONNECTED ; 
 int /*<<< orphan*/  LLCP_DM_NOCONN ; 
 size_t LLCP_HEADER_SIZE ; 
 struct nfc_llcp_sock* nfc_llcp_connecting_sock_get (struct nfc_llcp_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_llcp_dsap (struct sk_buff*) ; 
 int /*<<< orphan*/  nfc_llcp_parse_connection_tlv (struct nfc_llcp_sock*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  nfc_llcp_send_dm (struct nfc_llcp_local*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_llcp_sock_link (int /*<<< orphan*/ *,struct sock*) ; 
 int /*<<< orphan*/  nfc_llcp_sock_put (struct nfc_llcp_sock*) ; 
 int /*<<< orphan*/  nfc_llcp_sock_unlink (int /*<<< orphan*/ *,struct sock*) ; 
 int /*<<< orphan*/  nfc_llcp_ssap (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void nfc_llcp_recv_cc(struct nfc_llcp_local *local, struct sk_buff *skb)
{
	struct nfc_llcp_sock *llcp_sock;
	struct sock *sk;
	u8 dsap, ssap;

	dsap = nfc_llcp_dsap(skb);
	ssap = nfc_llcp_ssap(skb);

	llcp_sock = nfc_llcp_connecting_sock_get(local, dsap);
	if (llcp_sock == NULL) {
		pr_err("Invalid CC\n");
		nfc_llcp_send_dm(local, dsap, ssap, LLCP_DM_NOCONN);

		return;
	}

	sk = &llcp_sock->sk;

	/* Unlink from connecting and link to the client array */
	nfc_llcp_sock_unlink(&local->connecting_sockets, sk);
	nfc_llcp_sock_link(&local->sockets, sk);
	llcp_sock->dsap = ssap;

	nfc_llcp_parse_connection_tlv(llcp_sock, &skb->data[LLCP_HEADER_SIZE],
				      skb->len - LLCP_HEADER_SIZE);

	sk->sk_state = LLCP_CONNECTED;
	sk->sk_state_change(sk);

	nfc_llcp_sock_put(llcp_sock);
}