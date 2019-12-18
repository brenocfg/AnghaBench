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
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int dummy; } ;
struct cmtp_session {int flags; TYPE_1__* sock; int /*<<< orphan*/  terminate; } ;
struct TYPE_2__ {int /*<<< orphan*/  file; struct sock* sk; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct cmtp_session*) ; 
 int /*<<< orphan*/  CMTP_LOOPBACK ; 
 int /*<<< orphan*/  DEFINE_WAIT_FUNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  __cmtp_unlink_session (struct cmtp_session*) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmtp_detach_device (struct cmtp_session*) ; 
 int /*<<< orphan*/  cmtp_process_transmit (struct cmtp_session*) ; 
 int /*<<< orphan*/  cmtp_recv_frame (struct cmtp_session*,struct sk_buff*) ; 
 int /*<<< orphan*/  cmtp_session_sem ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cmtp_session*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  module_put_and_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_linearize (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wait_woken (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  woken_wake_function ; 

__attribute__((used)) static int cmtp_session(void *arg)
{
	struct cmtp_session *session = arg;
	struct sock *sk = session->sock->sk;
	struct sk_buff *skb;
	DEFINE_WAIT_FUNC(wait, woken_wake_function);

	BT_DBG("session %p", session);

	set_user_nice(current, -15);

	add_wait_queue(sk_sleep(sk), &wait);
	while (1) {
		if (atomic_read(&session->terminate))
			break;
		if (sk->sk_state != BT_CONNECTED)
			break;

		while ((skb = skb_dequeue(&sk->sk_receive_queue))) {
			skb_orphan(skb);
			if (!skb_linearize(skb))
				cmtp_recv_frame(session, skb);
			else
				kfree_skb(skb);
		}

		cmtp_process_transmit(session);

		/*
		 * wait_woken() performs the necessary memory barriers
		 * for us; see the header comment for this primitive.
		 */
		wait_woken(&wait, TASK_INTERRUPTIBLE, MAX_SCHEDULE_TIMEOUT);
	}
	remove_wait_queue(sk_sleep(sk), &wait);

	down_write(&cmtp_session_sem);

	if (!(session->flags & BIT(CMTP_LOOPBACK)))
		cmtp_detach_device(session);

	fput(session->sock->file);

	__cmtp_unlink_session(session);

	up_write(&cmtp_session_sem);

	kfree(session);
	module_put_and_exit(0);
	return 0;
}