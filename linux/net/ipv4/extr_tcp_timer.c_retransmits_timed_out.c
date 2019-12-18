#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sock {int sk_state; } ;
typedef  scalar_t__ s32 ;
struct TYPE_5__ {int /*<<< orphan*/  icsk_retransmits; } ;
struct TYPE_4__ {unsigned int retrans_stamp; } ;

/* Variables and functions */
 int TCPF_SYN_RECV ; 
 int TCPF_SYN_SENT ; 
 unsigned int TCP_RTO_MIN ; 
 TYPE_3__* inet_csk (struct sock*) ; 
 scalar_t__ likely (int) ; 
 unsigned int tcp_model_timeout (struct sock*,unsigned int,unsigned int) ; 
 TYPE_1__* tcp_sk (struct sock*) ; 
 unsigned int tcp_time_stamp (TYPE_1__*) ; 
 unsigned int tcp_timeout_init (struct sock*) ; 

__attribute__((used)) static bool retransmits_timed_out(struct sock *sk,
				  unsigned int boundary,
				  unsigned int timeout)
{
	unsigned int start_ts;

	if (!inet_csk(sk)->icsk_retransmits)
		return false;

	start_ts = tcp_sk(sk)->retrans_stamp;
	if (likely(timeout == 0)) {
		unsigned int rto_base = TCP_RTO_MIN;

		if ((1 << sk->sk_state) & (TCPF_SYN_SENT | TCPF_SYN_RECV))
			rto_base = tcp_timeout_init(sk);
		timeout = tcp_model_timeout(sk, boundary, rto_base);
	}

	return (s32)(tcp_time_stamp(tcp_sk(sk)) - start_ts - timeout) >= 0;
}