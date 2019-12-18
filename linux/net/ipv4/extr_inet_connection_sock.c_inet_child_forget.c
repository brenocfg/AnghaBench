#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sock {scalar_t__ sk_protocol; TYPE_1__* sk_prot; } ;
struct request_sock {struct sock* rsk_listener; } ;
struct TYPE_6__ {scalar_t__ tfo_listener; } ;
struct TYPE_5__ {int /*<<< orphan*/  fastopen_rsk; } ;
struct TYPE_4__ {int /*<<< orphan*/  orphan_count; int /*<<< orphan*/  (* disconnect ) (struct sock*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IPPROTO_TCP ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inet_csk_destroy_sock (struct sock*) ; 
 int /*<<< orphan*/  percpu_counter_inc (int /*<<< orphan*/ ) ; 
 struct request_sock* rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*,int /*<<< orphan*/ ) ; 
 TYPE_3__* tcp_rsk (struct request_sock*) ; 
 TYPE_2__* tcp_sk (struct sock*) ; 

__attribute__((used)) static void inet_child_forget(struct sock *sk, struct request_sock *req,
			      struct sock *child)
{
	sk->sk_prot->disconnect(child, O_NONBLOCK);

	sock_orphan(child);

	percpu_counter_inc(sk->sk_prot->orphan_count);

	if (sk->sk_protocol == IPPROTO_TCP && tcp_rsk(req)->tfo_listener) {
		BUG_ON(rcu_access_pointer(tcp_sk(child)->fastopen_rsk) != req);
		BUG_ON(sk != req->rsk_listener);

		/* Paranoid, to prevent race condition if
		 * an inbound pkt destined for child is
		 * blocked by sock lock in tcp_v4_rcv().
		 * Also to satisfy an assertion in
		 * tcp_v4_destroy_sock().
		 */
		RCU_INIT_POINTER(tcp_sk(child)->fastopen_rsk, NULL);
	}
	inet_csk_destroy_sock(child);
}