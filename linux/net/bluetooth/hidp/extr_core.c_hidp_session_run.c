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
struct hidp_session {int /*<<< orphan*/  terminate; TYPE_1__* ctrl_sock; int /*<<< orphan*/  ctrl_transmit; TYPE_1__* intr_sock; int /*<<< orphan*/  intr_transmit; } ;
struct TYPE_2__ {struct sock* sk; } ;

/* Variables and functions */
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  DEFINE_WAIT_FUNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hidp_process_transmit (struct hidp_session*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  hidp_recv_ctrl_frame (struct hidp_session*,struct sk_buff*) ; 
 int /*<<< orphan*/  hidp_recv_intr_frame (struct hidp_session*,struct sk_buff*) ; 
 int /*<<< orphan*/  hidp_session_wq ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_linearize (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wait_woken (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  woken_wake_function ; 

__attribute__((used)) static void hidp_session_run(struct hidp_session *session)
{
	struct sock *ctrl_sk = session->ctrl_sock->sk;
	struct sock *intr_sk = session->intr_sock->sk;
	struct sk_buff *skb;
	DEFINE_WAIT_FUNC(wait, woken_wake_function);

	add_wait_queue(&hidp_session_wq, &wait);
	for (;;) {
		/*
		 * This thread can be woken up two ways:
		 *  - You call hidp_session_terminate() which sets the
		 *    session->terminate flag and wakes this thread up.
		 *  - Via modifying the socket state of ctrl/intr_sock. This
		 *    thread is woken up by ->sk_state_changed().
		 */

		if (atomic_read(&session->terminate))
			break;

		if (ctrl_sk->sk_state != BT_CONNECTED ||
		    intr_sk->sk_state != BT_CONNECTED)
			break;

		/* parse incoming intr-skbs */
		while ((skb = skb_dequeue(&intr_sk->sk_receive_queue))) {
			skb_orphan(skb);
			if (!skb_linearize(skb))
				hidp_recv_intr_frame(session, skb);
			else
				kfree_skb(skb);
		}

		/* send pending intr-skbs */
		hidp_process_transmit(session, &session->intr_transmit,
				      session->intr_sock);

		/* parse incoming ctrl-skbs */
		while ((skb = skb_dequeue(&ctrl_sk->sk_receive_queue))) {
			skb_orphan(skb);
			if (!skb_linearize(skb))
				hidp_recv_ctrl_frame(session, skb);
			else
				kfree_skb(skb);
		}

		/* send pending ctrl-skbs */
		hidp_process_transmit(session, &session->ctrl_transmit,
				      session->ctrl_sock);

		/*
		 * wait_woken() performs the necessary memory barriers
		 * for us; see the header comment for this primitive.
		 */
		wait_woken(&wait, TASK_INTERRUPTIBLE, MAX_SCHEDULE_TIMEOUT);
	}
	remove_wait_queue(&hidp_session_wq, &wait);

	atomic_inc(&session->terminate);
}