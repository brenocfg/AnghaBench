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
struct TYPE_4__ {scalar_t__ expires; int /*<<< orphan*/  function; } ;
struct sock {TYPE_2__ sk_timer; int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {struct sock* sk; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  NR_STATE_0 ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nr_clear_queues (struct sock*) ; 
 int /*<<< orphan*/  nr_destroy_timer ; 
 int /*<<< orphan*/  nr_remove_socket (struct sock*) ; 
 TYPE_1__* nr_sk (struct sock*) ; 
 int /*<<< orphan*/  nr_start_heartbeat (struct sock*) ; 
 int /*<<< orphan*/  nr_stop_heartbeat (struct sock*) ; 
 int /*<<< orphan*/  nr_stop_idletimer (struct sock*) ; 
 int /*<<< orphan*/  nr_stop_t1timer (struct sock*) ; 
 int /*<<< orphan*/  nr_stop_t2timer (struct sock*) ; 
 int /*<<< orphan*/  nr_stop_t4timer (struct sock*) ; 
 scalar_t__ sk_has_allocations (struct sock*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 

void nr_destroy_socket(struct sock *sk)
{
	struct sk_buff *skb;

	nr_remove_socket(sk);

	nr_stop_heartbeat(sk);
	nr_stop_t1timer(sk);
	nr_stop_t2timer(sk);
	nr_stop_t4timer(sk);
	nr_stop_idletimer(sk);

	nr_clear_queues(sk);		/* Flush the queues */

	while ((skb = skb_dequeue(&sk->sk_receive_queue)) != NULL) {
		if (skb->sk != sk) { /* A pending connection */
			/* Queue the unaccepted socket for death */
			sock_set_flag(skb->sk, SOCK_DEAD);
			nr_start_heartbeat(skb->sk);
			nr_sk(skb->sk)->state = NR_STATE_0;
		}

		kfree_skb(skb);
	}

	if (sk_has_allocations(sk)) {
		/* Defer: outstanding buffers */
		sk->sk_timer.function = nr_destroy_timer;
		sk->sk_timer.expires  = jiffies + 2 * HZ;
		add_timer(&sk->sk_timer);
	} else
		sock_put(sk);
}