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
typedef  scalar_t__ u8 ;
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;} ;
struct sk_buff {int dummy; } ;
struct nfc_llcp_sock {struct sock sk; } ;
struct nfc_llcp_local {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ LLCP_CLOSED ; 
 scalar_t__ LLCP_CONNECTED ; 
 int /*<<< orphan*/  LLCP_DM_DISC ; 
 int /*<<< orphan*/  LLCP_DM_NOCONN ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  nfc_dep_link_down (int /*<<< orphan*/ ) ; 
 scalar_t__ nfc_llcp_dsap (struct sk_buff*) ; 
 int /*<<< orphan*/  nfc_llcp_send_dm (struct nfc_llcp_local*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct nfc_llcp_sock* nfc_llcp_sock_get (struct nfc_llcp_local*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  nfc_llcp_sock_put (struct nfc_llcp_sock*) ; 
 int /*<<< orphan*/  nfc_llcp_socket_purge (struct nfc_llcp_sock*) ; 
 scalar_t__ nfc_llcp_ssap (struct sk_buff*) ; 
 int /*<<< orphan*/  nfc_put_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void nfc_llcp_recv_disc(struct nfc_llcp_local *local,
			       struct sk_buff *skb)
{
	struct nfc_llcp_sock *llcp_sock;
	struct sock *sk;
	u8 dsap, ssap;

	dsap = nfc_llcp_dsap(skb);
	ssap = nfc_llcp_ssap(skb);

	if ((dsap == 0) && (ssap == 0)) {
		pr_debug("Connection termination");
		nfc_dep_link_down(local->dev);
		return;
	}

	llcp_sock = nfc_llcp_sock_get(local, dsap, ssap);
	if (llcp_sock == NULL) {
		nfc_llcp_send_dm(local, dsap, ssap, LLCP_DM_NOCONN);
		return;
	}

	sk = &llcp_sock->sk;
	lock_sock(sk);

	nfc_llcp_socket_purge(llcp_sock);

	if (sk->sk_state == LLCP_CLOSED) {
		release_sock(sk);
		nfc_llcp_sock_put(llcp_sock);
	}

	if (sk->sk_state == LLCP_CONNECTED) {
		nfc_put_device(local->dev);
		sk->sk_state = LLCP_CLOSED;
		sk->sk_state_change(sk);
	}

	nfc_llcp_send_dm(local, dsap, ssap, LLCP_DM_DISC);

	release_sock(sk);
	nfc_llcp_sock_put(llcp_sock);
}