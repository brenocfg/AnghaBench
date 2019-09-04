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
typedef  scalar_t__ u32 ;
struct tcp_sock {scalar_t__ lsndtime; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {scalar_t__ const lrcvtime; scalar_t__ ato; int pingpong; } ;
struct inet_connection_sock {TYPE_1__ icsk_ack; } ;

/* Variables and functions */
 int /*<<< orphan*/  CA_EVENT_TX_START ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  tcp_ca_event (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ tcp_jiffies32 ; 
 scalar_t__ tcp_packets_in_flight (struct tcp_sock*) ; 

__attribute__((used)) static void tcp_event_data_sent(struct tcp_sock *tp,
				struct sock *sk)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	const u32 now = tcp_jiffies32;

	if (tcp_packets_in_flight(tp) == 0)
		tcp_ca_event(sk, CA_EVENT_TX_START);

	tp->lsndtime = now;

	/* If it is a reply for ato after last received
	 * packet, enter pingpong mode.
	 */
	if ((u32)(now - icsk->icsk_ack.lrcvtime) < icsk->icsk_ack.ato)
		icsk->icsk_ack.pingpong = 1;
}