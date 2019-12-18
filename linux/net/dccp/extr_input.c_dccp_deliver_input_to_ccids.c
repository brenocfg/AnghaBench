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
struct TYPE_2__ {scalar_t__ qlen; } ;
struct sock {int sk_shutdown; TYPE_1__ sk_write_queue; } ;
struct sk_buff {int dummy; } ;
struct dccp_sock {int /*<<< orphan*/  dccps_hc_tx_ccid; int /*<<< orphan*/  dccps_hc_rx_ccid; } ;

/* Variables and functions */
 int RCV_SHUTDOWN ; 
 int SEND_SHUTDOWN ; 
 int /*<<< orphan*/  ccid_hc_rx_packet_recv (int /*<<< orphan*/ ,struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  ccid_hc_tx_packet_recv (int /*<<< orphan*/ ,struct sock*,struct sk_buff*) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 

__attribute__((used)) static void dccp_deliver_input_to_ccids(struct sock *sk, struct sk_buff *skb)
{
	const struct dccp_sock *dp = dccp_sk(sk);

	/* Don't deliver to RX CCID when node has shut down read end. */
	if (!(sk->sk_shutdown & RCV_SHUTDOWN))
		ccid_hc_rx_packet_recv(dp->dccps_hc_rx_ccid, sk, skb);
	/*
	 * Until the TX queue has been drained, we can not honour SHUT_WR, since
	 * we need received feedback as input to adjust congestion control.
	 */
	if (sk->sk_write_queue.qlen > 0 || !(sk->sk_shutdown & SEND_SHUTDOWN))
		ccid_hc_tx_packet_recv(dp->dccps_hc_tx_ccid, sk, skb);
}