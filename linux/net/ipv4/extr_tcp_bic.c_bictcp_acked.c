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
struct sock {int dummy; } ;
struct inet_connection_sock {scalar_t__ icsk_ca_state; } ;
struct bictcp {int delayed_ack; } ;
struct ack_sample {int pkts_acked; } ;

/* Variables and functions */
 int ACK_RATIO_SHIFT ; 
 scalar_t__ TCP_CA_Open ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 struct bictcp* inet_csk_ca (struct sock*) ; 

__attribute__((used)) static void bictcp_acked(struct sock *sk, const struct ack_sample *sample)
{
	const struct inet_connection_sock *icsk = inet_csk(sk);

	if (icsk->icsk_ca_state == TCP_CA_Open) {
		struct bictcp *ca = inet_csk_ca(sk);

		ca->delayed_ack += sample->pkts_acked -
			(ca->delayed_ack >> ACK_RATIO_SHIFT);
	}
}