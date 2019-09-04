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
typedef  int u8 ;
struct sock {int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_state; int /*<<< orphan*/  sk_err; } ;
struct sk_buff {int* data; } ;
struct nfc_llcp_sock {struct sock sk; } ;
struct nfc_llcp_local {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  LLCP_CLOSED ; 
#define  LLCP_DM_NOBOUND 129 
#define  LLCP_DM_REJ 128 
 struct nfc_llcp_sock* nfc_llcp_connecting_sock_get (struct nfc_llcp_local*,int) ; 
 int nfc_llcp_dsap (struct sk_buff*) ; 
 struct nfc_llcp_sock* nfc_llcp_sock_get (struct nfc_llcp_local*,int,int) ; 
 int /*<<< orphan*/  nfc_llcp_sock_put (struct nfc_llcp_sock*) ; 
 int nfc_llcp_ssap (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void nfc_llcp_recv_dm(struct nfc_llcp_local *local, struct sk_buff *skb)
{
	struct nfc_llcp_sock *llcp_sock;
	struct sock *sk;
	u8 dsap, ssap, reason;

	dsap = nfc_llcp_dsap(skb);
	ssap = nfc_llcp_ssap(skb);
	reason = skb->data[2];

	pr_debug("%d %d reason %d\n", ssap, dsap, reason);

	switch (reason) {
	case LLCP_DM_NOBOUND:
	case LLCP_DM_REJ:
		llcp_sock = nfc_llcp_connecting_sock_get(local, dsap);
		break;

	default:
		llcp_sock = nfc_llcp_sock_get(local, dsap, ssap);
		break;
	}

	if (llcp_sock == NULL) {
		pr_debug("Already closed\n");
		return;
	}

	sk = &llcp_sock->sk;

	sk->sk_err = ENXIO;
	sk->sk_state = LLCP_CLOSED;
	sk->sk_state_change(sk);

	nfc_llcp_sock_put(llcp_sock);
}