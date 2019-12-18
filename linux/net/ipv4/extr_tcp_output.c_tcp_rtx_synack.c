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
struct tcp_request_sock_ops {int (* send_synack ) (struct sock const*,int /*<<< orphan*/ *,struct flowi*,struct request_sock*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct sock {int dummy; } ;
struct request_sock {int dummy; } ;
struct flowi {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  txhash; struct tcp_request_sock_ops* af_specific; } ;
struct TYPE_3__ {int /*<<< orphan*/  total_retrans; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_MIB_TCPSYNRETRANS ; 
 int /*<<< orphan*/  TCP_MIB_RETRANSSEGS ; 
 int /*<<< orphan*/  TCP_SYNACK_NORMAL ; 
 int /*<<< orphan*/  __NET_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __TCP_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_tx_rndhash () ; 
 int /*<<< orphan*/  sock_net (struct sock const*) ; 
 int stub1 (struct sock const*,int /*<<< orphan*/ *,struct flowi*,struct request_sock*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_passive_fastopen (struct sock const*) ; 
 TYPE_2__* tcp_rsk (struct request_sock*) ; 
 TYPE_1__* tcp_sk (struct sock const*) ; 
 int /*<<< orphan*/  trace_tcp_retransmit_synack (struct sock const*,struct request_sock*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int tcp_rtx_synack(const struct sock *sk, struct request_sock *req)
{
	const struct tcp_request_sock_ops *af_ops = tcp_rsk(req)->af_specific;
	struct flowi fl;
	int res;

	tcp_rsk(req)->txhash = net_tx_rndhash();
	res = af_ops->send_synack(sk, NULL, &fl, req, NULL, TCP_SYNACK_NORMAL);
	if (!res) {
		__TCP_INC_STATS(sock_net(sk), TCP_MIB_RETRANSSEGS);
		__NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPSYNRETRANS);
		if (unlikely(tcp_passive_fastopen(sk)))
			tcp_sk(sk)->total_retrans++;
		trace_tcp_retransmit_synack(sk, req);
	}
	return res;
}