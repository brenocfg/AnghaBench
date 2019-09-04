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
struct sock {int /*<<< orphan*/  sk_write_queue; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int llc_conn_send_pdus (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

int llc_conn_send_pdu(struct sock *sk, struct sk_buff *skb)
{
	/* queue PDU to send to MAC layer */
	skb_queue_tail(&sk->sk_write_queue, skb);
	return llc_conn_send_pdus(sk, skb);
}