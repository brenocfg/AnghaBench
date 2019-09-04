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
struct sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk; } ;
struct pep_sock {TYPE_1__ pn_sk; int /*<<< orphan*/  hlist; struct sock* listener; } ;

/* Variables and functions */
 scalar_t__ hlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 struct pep_sock* pep_sk (struct sock*) ; 
 int /*<<< orphan*/  pn_sock_unhash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sk_del_node_init (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

__attribute__((used)) static void pep_sock_unhash(struct sock *sk)
{
	struct pep_sock *pn = pep_sk(sk);
	struct sock *skparent = NULL;

	lock_sock(sk);

	if (pn->listener != NULL) {
		skparent = pn->listener;
		pn->listener = NULL;
		release_sock(sk);

		pn = pep_sk(skparent);
		lock_sock(skparent);
		sk_del_node_init(sk);
		sk = skparent;
	}

	/* Unhash a listening sock only when it is closed
	 * and all of its active connected pipes are closed. */
	if (hlist_empty(&pn->hlist))
		pn_sock_unhash(&pn->pn_sk.sk);
	release_sock(sk);

	if (skparent)
		sock_put(skparent);
}