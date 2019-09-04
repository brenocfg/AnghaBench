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
typedef  int u32 ;
struct tcp_sock {scalar_t__ syn_data_acked; scalar_t__ syn_data; scalar_t__ syn_fastopen; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {int icsk_retransmits; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_MIB_TCPFASTOPENACTIVEFAIL ; 
 int /*<<< orphan*/  NET_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  tcp_fastopen_active_disable (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

void tcp_fastopen_active_detect_blackhole(struct sock *sk, bool expired)
{
	u32 timeouts = inet_csk(sk)->icsk_retransmits;
	struct tcp_sock *tp = tcp_sk(sk);

	/* Broken middle-boxes may black-hole Fast Open connection during or
	 * even after the handshake. Be extremely conservative and pause
	 * Fast Open globally after hitting the third consecutive timeout or
	 * exceeding the configured timeout limit.
	 */
	if ((tp->syn_fastopen || tp->syn_data || tp->syn_data_acked) &&
	    (timeouts == 2 || (timeouts < 2 && expired))) {
		tcp_fastopen_active_disable(sk);
		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPFASTOPENACTIVEFAIL);
	}
}