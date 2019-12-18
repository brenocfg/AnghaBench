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
typedef  void* u64 ;
struct tcp_sock {scalar_t__ app_limited; int /*<<< orphan*/  delivered; void* delivered_mstamp; void* first_tx_mstamp; int /*<<< orphan*/  packets_out; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int is_app_limited; int /*<<< orphan*/  delivered; void* delivered_mstamp; void* first_tx_mstamp; } ;
struct TYPE_4__ {TYPE_1__ tx; } ;

/* Variables and functions */
 TYPE_2__* TCP_SKB_CB (struct sk_buff*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 void* tcp_skb_timestamp_us (struct sk_buff*) ; 

void tcp_rate_skb_sent(struct sock *sk, struct sk_buff *skb)
{
	struct tcp_sock *tp = tcp_sk(sk);

	 /* In general we need to start delivery rate samples from the
	  * time we received the most recent ACK, to ensure we include
	  * the full time the network needs to deliver all in-flight
	  * packets. If there are no packets in flight yet, then we
	  * know that any ACKs after now indicate that the network was
	  * able to deliver those packets completely in the sampling
	  * interval between now and the next ACK.
	  *
	  * Note that we use packets_out instead of tcp_packets_in_flight(tp)
	  * because the latter is a guess based on RTO and loss-marking
	  * heuristics. We don't want spurious RTOs or loss markings to cause
	  * a spuriously small time interval, causing a spuriously high
	  * bandwidth estimate.
	  */
	if (!tp->packets_out) {
		u64 tstamp_us = tcp_skb_timestamp_us(skb);

		tp->first_tx_mstamp  = tstamp_us;
		tp->delivered_mstamp = tstamp_us;
	}

	TCP_SKB_CB(skb)->tx.first_tx_mstamp	= tp->first_tx_mstamp;
	TCP_SKB_CB(skb)->tx.delivered_mstamp	= tp->delivered_mstamp;
	TCP_SKB_CB(skb)->tx.delivered		= tp->delivered;
	TCP_SKB_CB(skb)->tx.is_app_limited	= tp->app_limited ? 1 : 0;
}