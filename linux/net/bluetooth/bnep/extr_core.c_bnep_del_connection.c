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
struct bnep_session {TYPE_1__* sock; int /*<<< orphan*/  terminate; } ;
struct bnep_conndel_req {int flags; int /*<<< orphan*/  dst; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int EINVAL ; 
 int ENOENT ; 
 struct bnep_session* __bnep_get_session (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnep_session_sem ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_sleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ ) ; 

int bnep_del_connection(struct bnep_conndel_req *req)
{
	u32 valid_flags = 0;
	struct bnep_session *s;
	int  err = 0;

	BT_DBG("");

	if (req->flags & ~valid_flags)
		return -EINVAL;

	down_read(&bnep_session_sem);

	s = __bnep_get_session(req->dst);
	if (s) {
		atomic_inc(&s->terminate);
		wake_up_interruptible(sk_sleep(s->sock->sk));
	} else
		err = -ENOENT;

	up_read(&bnep_session_sem);
	return err;
}