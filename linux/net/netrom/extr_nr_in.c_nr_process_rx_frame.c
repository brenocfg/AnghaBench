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
struct sk_buff {int* data; } ;
struct nr_sock {int state; } ;

/* Variables and functions */
 int NR_STATE_0 ; 
#define  NR_STATE_1 130 
#define  NR_STATE_2 129 
#define  NR_STATE_3 128 
 int /*<<< orphan*/  nr_kick (struct sock*) ; 
 struct nr_sock* nr_sk (struct sock*) ; 
 int nr_state1_machine (struct sock*,struct sk_buff*,int) ; 
 int nr_state2_machine (struct sock*,struct sk_buff*,int) ; 
 int nr_state3_machine (struct sock*,struct sk_buff*,int) ; 

int nr_process_rx_frame(struct sock *sk, struct sk_buff *skb)
{
	struct nr_sock *nr = nr_sk(sk);
	int queued = 0, frametype;

	if (nr->state == NR_STATE_0)
		return 0;

	frametype = skb->data[19];

	switch (nr->state) {
	case NR_STATE_1:
		queued = nr_state1_machine(sk, skb, frametype);
		break;
	case NR_STATE_2:
		queued = nr_state2_machine(sk, skb, frametype);
		break;
	case NR_STATE_3:
		queued = nr_state3_machine(sk, skb, frametype);
		break;
	}

	nr_kick(sk);

	return queued;
}