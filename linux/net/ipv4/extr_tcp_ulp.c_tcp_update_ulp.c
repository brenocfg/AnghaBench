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
struct sock {struct proto* sk_prot; } ;
struct proto {int dummy; } ;
struct inet_connection_sock {TYPE_1__* icsk_ulp_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* update ) (struct sock*,struct proto*) ;} ;

/* Variables and functions */
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*,struct proto*) ; 

void tcp_update_ulp(struct sock *sk, struct proto *proto)
{
	struct inet_connection_sock *icsk = inet_csk(sk);

	if (!icsk->icsk_ulp_ops) {
		sk->sk_prot = proto;
		return;
	}

	if (icsk->icsk_ulp_ops->update)
		icsk->icsk_ulp_ops->update(sk, proto);
}