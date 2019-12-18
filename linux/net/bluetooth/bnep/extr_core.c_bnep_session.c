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
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  sk_err; int /*<<< orphan*/  sk_write_queue; int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct bnep_session {TYPE_1__* sock; int /*<<< orphan*/  terminate; struct net_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  file; struct sock* sk; } ;

/* Variables and functions */
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int /*<<< orphan*/  DEFINE_WAIT_FUNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EUNATCH ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  __bnep_unlink_session (struct bnep_session*) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnep_rx_frame (struct bnep_session*,struct sk_buff*) ; 
 int /*<<< orphan*/  bnep_session_sem ; 
 scalar_t__ bnep_tx_frame (struct bnep_session*,struct sk_buff*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  module_put_and_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_linearize (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wait_woken (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  woken_wake_function ; 

__attribute__((used)) static int bnep_session(void *arg)
{
	struct bnep_session *s = arg;
	struct net_device *dev = s->dev;
	struct sock *sk = s->sock->sk;
	struct sk_buff *skb;
	DEFINE_WAIT_FUNC(wait, woken_wake_function);

	BT_DBG("");

	set_user_nice(current, -15);

	add_wait_queue(sk_sleep(sk), &wait);
	while (1) {
		if (atomic_read(&s->terminate))
			break;
		/* RX */
		while ((skb = skb_dequeue(&sk->sk_receive_queue))) {
			skb_orphan(skb);
			if (!skb_linearize(skb))
				bnep_rx_frame(s, skb);
			else
				kfree_skb(skb);
		}

		if (sk->sk_state != BT_CONNECTED)
			break;

		/* TX */
		while ((skb = skb_dequeue(&sk->sk_write_queue)))
			if (bnep_tx_frame(s, skb))
				break;
		netif_wake_queue(dev);

		/*
		 * wait_woken() performs the necessary memory barriers
		 * for us; see the header comment for this primitive.
		 */
		wait_woken(&wait, TASK_INTERRUPTIBLE, MAX_SCHEDULE_TIMEOUT);
	}
	remove_wait_queue(sk_sleep(sk), &wait);

	/* Cleanup session */
	down_write(&bnep_session_sem);

	/* Delete network device */
	unregister_netdev(dev);

	/* Wakeup user-space polling for socket errors */
	s->sock->sk->sk_err = EUNATCH;

	wake_up_interruptible(sk_sleep(s->sock->sk));

	/* Release the socket */
	fput(s->sock->file);

	__bnep_unlink_session(s);

	up_write(&bnep_session_sem);
	free_netdev(dev);
	module_put_and_exit(0);
	return 0;
}