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
struct sock {int dummy; } ;
struct nfc_llcp_sock {struct sock* parent; int /*<<< orphan*/  accept_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nfc_llcp_sock* nfc_llcp_sock (struct sock*) ; 
 int /*<<< orphan*/  sk_acceptq_added (struct sock*) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 

void nfc_llcp_accept_enqueue(struct sock *parent, struct sock *sk)
{
	struct nfc_llcp_sock *llcp_sock = nfc_llcp_sock(sk);
	struct nfc_llcp_sock *llcp_sock_parent = nfc_llcp_sock(parent);

	/* Lock will be free from unlink */
	sock_hold(sk);

	list_add_tail(&llcp_sock->accept_queue,
		      &llcp_sock_parent->accept_queue);
	llcp_sock->parent = parent;
	sk_acceptq_added(parent);
}