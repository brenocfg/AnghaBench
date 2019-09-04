#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct hidp_session {TYPE_2__* ctrl_sock; TYPE_1__* intr_sock; } ;
struct TYPE_6__ {void* sk_err; } ;
struct TYPE_5__ {TYPE_3__* sk; } ;
struct TYPE_4__ {TYPE_3__* sk; } ;

/* Variables and functions */
 void* EUNATCH ; 
 struct hidp_session* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hidp_session_terminate (struct hidp_session*) ; 
 struct hidp_session* session ; 
 int /*<<< orphan*/  sk_sleep (TYPE_3__*) ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hidp_idle_timeout(struct timer_list *t)
{
	struct hidp_session *session = from_timer(session, t, timer);

	/* The HIDP user-space API only contains calls to add and remove
	 * devices. There is no way to forward events of any kind. Therefore,
	 * we have to forcefully disconnect a device on idle-timeouts. This is
	 * unfortunate and weird API design, but it is spec-compliant and
	 * required for backwards-compatibility. Hence, on idle-timeout, we
	 * signal driver-detach events, so poll() will be woken up with an
	 * error-condition on both sockets.
	 */

	session->intr_sock->sk->sk_err = EUNATCH;
	session->ctrl_sock->sk->sk_err = EUNATCH;
	wake_up_interruptible(sk_sleep(session->intr_sock->sk));
	wake_up_interruptible(sk_sleep(session->ctrl_sock->sk));

	hidp_session_terminate(session);
}