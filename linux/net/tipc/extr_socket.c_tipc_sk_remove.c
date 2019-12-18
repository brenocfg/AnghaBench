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
struct sock {int /*<<< orphan*/  sk_refcnt; } ;
struct tipc_sock {int /*<<< orphan*/  node; struct sock sk; } ;
struct tipc_net {int /*<<< orphan*/  sk_rht; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __sock_put (struct sock*) ; 
 struct tipc_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  tipc_net_id ; 
 int /*<<< orphan*/  tsk_rht_params ; 

__attribute__((used)) static void tipc_sk_remove(struct tipc_sock *tsk)
{
	struct sock *sk = &tsk->sk;
	struct tipc_net *tn = net_generic(sock_net(sk), tipc_net_id);

	if (!rhashtable_remove_fast(&tn->sk_rht, &tsk->node, tsk_rht_params)) {
		WARN_ON(refcount_read(&sk->sk_refcnt) == 1);
		__sock_put(sk);
	}
}