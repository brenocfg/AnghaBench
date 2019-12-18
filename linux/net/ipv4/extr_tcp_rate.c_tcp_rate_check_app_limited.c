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
struct tcp_sock {scalar_t__ write_seq; scalar_t__ snd_nxt; scalar_t__ mss_cache; scalar_t__ snd_cwnd; scalar_t__ lost_out; scalar_t__ retrans_out; int app_limited; scalar_t__ delivered; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 scalar_t__ SKB_TRUESIZE (int) ; 
 scalar_t__ sk_wmem_alloc_get (struct sock*) ; 
 scalar_t__ tcp_packets_in_flight (struct tcp_sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

void tcp_rate_check_app_limited(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);

	if (/* We have less than one packet to send. */
	    tp->write_seq - tp->snd_nxt < tp->mss_cache &&
	    /* Nothing in sending host's qdisc queues or NIC tx queue. */
	    sk_wmem_alloc_get(sk) < SKB_TRUESIZE(1) &&
	    /* We are not limited by CWND. */
	    tcp_packets_in_flight(tp) < tp->snd_cwnd &&
	    /* All lost packets have been retransmitted. */
	    tp->lost_out <= tp->retrans_out)
		tp->app_limited =
			(tp->delivered + tcp_packets_in_flight(tp)) ? : 1;
}