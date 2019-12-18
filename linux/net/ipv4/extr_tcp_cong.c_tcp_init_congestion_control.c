#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct inet_connection_sock {TYPE_1__* icsk_ca_ops; } ;
struct TYPE_4__ {scalar_t__ prior_ssthresh; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* init ) (struct sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  INET_ECN_dontxmit (struct sock*) ; 
 int /*<<< orphan*/  INET_ECN_xmit (struct sock*) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 scalar_t__ tcp_ca_needs_ecn (struct sock*) ; 
 TYPE_2__* tcp_sk (struct sock*) ; 

void tcp_init_congestion_control(struct sock *sk)
{
	const struct inet_connection_sock *icsk = inet_csk(sk);

	tcp_sk(sk)->prior_ssthresh = 0;
	if (icsk->icsk_ca_ops->init)
		icsk->icsk_ca_ops->init(sk);
	if (tcp_ca_needs_ecn(sk))
		INET_ECN_xmit(sk);
	else
		INET_ECN_dontxmit(sk);
}