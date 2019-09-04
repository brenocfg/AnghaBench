#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct request_sock {int num_timeout; TYPE_1__* rsk_ops; } ;
struct inet_connection_sock {int /*<<< orphan*/  icsk_retransmits; scalar_t__ icsk_syn_retries; } ;
struct TYPE_6__ {int sysctl_tcp_synack_retries; } ;
struct TYPE_8__ {TYPE_2__ ipv4; } ;
struct TYPE_7__ {struct request_sock* fastopen_rsk; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* syn_ack_timeout ) (struct request_sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ICSK_TIME_RETRANS ; 
 int /*<<< orphan*/  TCP_RTO_MAX ; 
 int TCP_TIMEOUT_INIT ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_reset_xmit_timer (struct sock*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_rtx_syn_ack (struct sock*,struct request_sock*) ; 
 TYPE_4__* sock_net (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct request_sock*) ; 
 TYPE_3__* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_write_err (struct sock*) ; 

__attribute__((used)) static void tcp_fastopen_synack_timer(struct sock *sk)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	int max_retries = icsk->icsk_syn_retries ? :
	    sock_net(sk)->ipv4.sysctl_tcp_synack_retries + 1; /* add one more retry for fastopen */
	struct request_sock *req;

	req = tcp_sk(sk)->fastopen_rsk;
	req->rsk_ops->syn_ack_timeout(req);

	if (req->num_timeout >= max_retries) {
		tcp_write_err(sk);
		return;
	}
	/* XXX (TFO) - Unlike regular SYN-ACK retransmit, we ignore error
	 * returned from rtx_syn_ack() to make it more persistent like
	 * regular retransmit because if the child socket has been accepted
	 * it's not good to give up too easily.
	 */
	inet_rtx_syn_ack(sk, req);
	req->num_timeout++;
	icsk->icsk_retransmits++;
	inet_csk_reset_xmit_timer(sk, ICSK_TIME_RETRANS,
			  TCP_TIMEOUT_INIT << req->num_timeout, TCP_RTO_MAX);
}