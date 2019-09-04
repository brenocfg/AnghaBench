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
struct sock {scalar_t__ sk_rcvbuf; int /*<<< orphan*/  sk_rmem_alloc; int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct rfcomm_dlc {struct sock* owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfcomm_dlc_throttle (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void rfcomm_sk_data_ready(struct rfcomm_dlc *d, struct sk_buff *skb)
{
	struct sock *sk = d->owner;
	if (!sk)
		return;

	atomic_add(skb->len, &sk->sk_rmem_alloc);
	skb_queue_tail(&sk->sk_receive_queue, skb);
	sk->sk_data_ready(sk);

	if (atomic_read(&sk->sk_rmem_alloc) >= sk->sk_rcvbuf)
		rfcomm_dlc_throttle(d);
}