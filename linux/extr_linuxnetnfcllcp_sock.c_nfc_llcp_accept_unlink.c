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
struct sock {int /*<<< orphan*/  sk_state; } ;
struct nfc_llcp_sock {int /*<<< orphan*/ * parent; int /*<<< orphan*/  accept_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 struct nfc_llcp_sock* nfc_llcp_sock (struct sock*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_acceptq_removed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

void nfc_llcp_accept_unlink(struct sock *sk)
{
	struct nfc_llcp_sock *llcp_sock = nfc_llcp_sock(sk);

	pr_debug("state %d\n", sk->sk_state);

	list_del_init(&llcp_sock->accept_queue);
	sk_acceptq_removed(llcp_sock->parent);
	llcp_sock->parent = NULL;

	sock_put(sk);
}