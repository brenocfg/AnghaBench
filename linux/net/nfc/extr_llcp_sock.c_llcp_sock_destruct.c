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
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  sk_receive_queue; } ;
struct nfc_llcp_sock {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ LLCP_CONNECTED ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 struct nfc_llcp_sock* nfc_llcp_sock (struct sock*) ; 
 int /*<<< orphan*/  nfc_llcp_sock_free (struct nfc_llcp_sock*) ; 
 int /*<<< orphan*/  nfc_put_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct sock*) ; 
 int /*<<< orphan*/  pr_err (char*,struct sock*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void llcp_sock_destruct(struct sock *sk)
{
	struct nfc_llcp_sock *llcp_sock = nfc_llcp_sock(sk);

	pr_debug("%p\n", sk);

	if (sk->sk_state == LLCP_CONNECTED)
		nfc_put_device(llcp_sock->dev);

	skb_queue_purge(&sk->sk_receive_queue);

	nfc_llcp_sock_free(llcp_sock);

	if (!sock_flag(sk, SOCK_DEAD)) {
		pr_err("Freeing alive NFC LLCP socket %p\n", sk);
		return;
	}
}