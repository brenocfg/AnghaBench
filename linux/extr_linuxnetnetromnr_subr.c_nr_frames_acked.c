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
struct sk_buff {int dummy; } ;
struct nr_sock {unsigned short va; int /*<<< orphan*/  ack_queue; } ;

/* Variables and functions */
 int NR_MODULUS ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct nr_sock* nr_sk (struct sock*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * skb_peek (int /*<<< orphan*/ *) ; 

void nr_frames_acked(struct sock *sk, unsigned short nr)
{
	struct nr_sock *nrom = nr_sk(sk);
	struct sk_buff *skb;

	/*
	 * Remove all the ack-ed frames from the ack queue.
	 */
	if (nrom->va != nr) {
		while (skb_peek(&nrom->ack_queue) != NULL && nrom->va != nr) {
			skb = skb_dequeue(&nrom->ack_queue);
			kfree_skb(skb);
			nrom->va = (nrom->va + 1) % NR_MODULUS;
		}
	}
}