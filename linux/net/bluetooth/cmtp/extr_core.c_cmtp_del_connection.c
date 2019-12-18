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
typedef  int u32 ;
struct cmtp_session {TYPE_1__* sock; int /*<<< orphan*/  terminate; int /*<<< orphan*/  transmit; } ;
struct cmtp_conndel_req {int flags; int /*<<< orphan*/  bdaddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int EINVAL ; 
 int ENOENT ; 
 struct cmtp_session* __cmtp_get_session (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmtp_session_sem ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_sleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ ) ; 

int cmtp_del_connection(struct cmtp_conndel_req *req)
{
	u32 valid_flags = 0;
	struct cmtp_session *session;
	int err = 0;

	BT_DBG("");

	if (req->flags & ~valid_flags)
		return -EINVAL;

	down_read(&cmtp_session_sem);

	session = __cmtp_get_session(&req->bdaddr);
	if (session) {
		/* Flush the transmit queue */
		skb_queue_purge(&session->transmit);

		/* Stop session thread */
		atomic_inc(&session->terminate);

		/*
		 * See the comment preceding the call to wait_woken()
		 * in cmtp_session().
		 */
		wake_up_interruptible(sk_sleep(session->sock->sk));
	} else
		err = -ENOENT;

	up_read(&cmtp_session_sem);
	return err;
}