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
struct hidp_session {int /*<<< orphan*/  user; int /*<<< orphan*/  conn; int /*<<< orphan*/  report_queue; TYPE_2__* intr_sock; int /*<<< orphan*/  state_queue; int /*<<< orphan*/  state; TYPE_1__* ctrl_sock; } ;
struct TYPE_4__ {int /*<<< orphan*/  sk; } ;
struct TYPE_3__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hidp_session*) ; 
 int /*<<< orphan*/  DEFINE_WAIT_FUNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctrl_wait ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  hidp_del_timer (struct hidp_session*) ; 
 int /*<<< orphan*/  hidp_session_get (struct hidp_session*) ; 
 int /*<<< orphan*/  hidp_session_put (struct hidp_session*) ; 
 int /*<<< orphan*/  hidp_session_run (struct hidp_session*) ; 
 int /*<<< orphan*/  hidp_session_wake_function ; 
 int /*<<< orphan*/  hidp_set_timer (struct hidp_session*) ; 
 int /*<<< orphan*/  intr_wait ; 
 int /*<<< orphan*/  l2cap_unregister_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put_and_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sk_sleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hidp_session_thread(void *arg)
{
	struct hidp_session *session = arg;
	DEFINE_WAIT_FUNC(ctrl_wait, hidp_session_wake_function);
	DEFINE_WAIT_FUNC(intr_wait, hidp_session_wake_function);

	BT_DBG("session %p", session);

	/* initialize runtime environment */
	hidp_session_get(session);
	__module_get(THIS_MODULE);
	set_user_nice(current, -15);
	hidp_set_timer(session);

	add_wait_queue(sk_sleep(session->ctrl_sock->sk), &ctrl_wait);
	add_wait_queue(sk_sleep(session->intr_sock->sk), &intr_wait);
	/* This memory barrier is paired with wq_has_sleeper(). See
	 * sock_poll_wait() for more information why this is needed. */
	smp_mb();

	/* notify synchronous startup that we're ready */
	atomic_inc(&session->state);
	wake_up(&session->state_queue);

	/* run session */
	hidp_session_run(session);

	/* cleanup runtime environment */
	remove_wait_queue(sk_sleep(session->intr_sock->sk), &intr_wait);
	remove_wait_queue(sk_sleep(session->intr_sock->sk), &ctrl_wait);
	wake_up_interruptible(&session->report_queue);
	hidp_del_timer(session);

	/*
	 * If we stopped ourself due to any internal signal, we should try to
	 * unregister our own session here to avoid having it linger until the
	 * parent l2cap_conn dies or user-space cleans it up.
	 * This does not deadlock as we don't do any synchronous shutdown.
	 * Instead, this call has the same semantics as if user-space tried to
	 * delete the session.
	 */
	l2cap_unregister_user(session->conn, &session->user);
	hidp_session_put(session);

	module_put_and_exit(0);
	return 0;
}