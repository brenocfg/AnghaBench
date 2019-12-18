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
struct sk_buff {int dummy; } ;
struct ccid2_hc_rx_sock {scalar_t__ rx_num_data_pkts; } ;
struct TYPE_2__ {scalar_t__ dccps_r_ack_ratio; } ;

/* Variables and functions */
 struct ccid2_hc_rx_sock* ccid2_hc_rx_sk (struct sock*) ; 
 int /*<<< orphan*/  dccp_data_packet (struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_send_ack (struct sock*) ; 
 TYPE_1__* dccp_sk (struct sock*) ; 

__attribute__((used)) static void ccid2_hc_rx_packet_recv(struct sock *sk, struct sk_buff *skb)
{
	struct ccid2_hc_rx_sock *hc = ccid2_hc_rx_sk(sk);

	if (!dccp_data_packet(skb))
		return;

	if (++hc->rx_num_data_pkts >= dccp_sk(sk)->dccps_r_ack_ratio) {
		dccp_send_ack(sk);
		hc->rx_num_data_pkts = 0;
	}
}