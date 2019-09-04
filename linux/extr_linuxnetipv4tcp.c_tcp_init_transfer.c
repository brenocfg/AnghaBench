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
struct inet_connection_sock {TYPE_1__* icsk_af_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rebuild_header ) (struct sock*) ;} ;

/* Variables and functions */
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  tcp_call_bpf (struct sock*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_init_buffer_space (struct sock*) ; 
 int /*<<< orphan*/  tcp_init_congestion_control (struct sock*) ; 
 int /*<<< orphan*/  tcp_init_metrics (struct sock*) ; 
 int /*<<< orphan*/  tcp_mtup_init (struct sock*) ; 

void tcp_init_transfer(struct sock *sk, int bpf_op)
{
	struct inet_connection_sock *icsk = inet_csk(sk);

	tcp_mtup_init(sk);
	icsk->icsk_af_ops->rebuild_header(sk);
	tcp_init_metrics(sk);
	tcp_call_bpf(sk, bpf_op, 0, NULL);
	tcp_init_congestion_control(sk);
	tcp_init_buffer_space(sk);
}