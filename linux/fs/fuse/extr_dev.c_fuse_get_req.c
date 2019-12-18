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
typedef  scalar_t__ uid_t ;
struct TYPE_3__ {scalar_t__ uid; scalar_t__ gid; int /*<<< orphan*/  pid; } ;
struct TYPE_4__ {TYPE_1__ h; } ;
struct fuse_req {TYPE_2__ in; int /*<<< orphan*/  flags; } ;
struct fuse_conn {int /*<<< orphan*/  pid_ns; int /*<<< orphan*/  user_ns; int /*<<< orphan*/  blocked_waitq; scalar_t__ conn_error; int /*<<< orphan*/  connected; int /*<<< orphan*/  num_waiting; } ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int ECONNREFUSED ; 
 int EINTR ; 
 int ENOMEM ; 
 int ENOTCONN ; 
 int EOVERFLOW ; 
 struct fuse_req* ERR_PTR (int) ; 
 int /*<<< orphan*/  FR_BACKGROUND ; 
 int /*<<< orphan*/  FR_WAITING ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 scalar_t__ from_kgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ from_kuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fuse_block_alloc (struct fuse_conn*,int) ; 
 int /*<<< orphan*/  fuse_drop_waiting (struct fuse_conn*) ; 
 int /*<<< orphan*/  fuse_put_request (struct fuse_conn*,struct fuse_req*) ; 
 struct fuse_req* fuse_request_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pid_nr_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  task_pid (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ wait_event_killable_exclusive (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct fuse_req *fuse_get_req(struct fuse_conn *fc, bool for_background)
{
	struct fuse_req *req;
	int err;
	atomic_inc(&fc->num_waiting);

	if (fuse_block_alloc(fc, for_background)) {
		err = -EINTR;
		if (wait_event_killable_exclusive(fc->blocked_waitq,
				!fuse_block_alloc(fc, for_background)))
			goto out;
	}
	/* Matches smp_wmb() in fuse_set_initialized() */
	smp_rmb();

	err = -ENOTCONN;
	if (!fc->connected)
		goto out;

	err = -ECONNREFUSED;
	if (fc->conn_error)
		goto out;

	req = fuse_request_alloc(GFP_KERNEL);
	err = -ENOMEM;
	if (!req) {
		if (for_background)
			wake_up(&fc->blocked_waitq);
		goto out;
	}

	req->in.h.uid = from_kuid(fc->user_ns, current_fsuid());
	req->in.h.gid = from_kgid(fc->user_ns, current_fsgid());
	req->in.h.pid = pid_nr_ns(task_pid(current), fc->pid_ns);

	__set_bit(FR_WAITING, &req->flags);
	if (for_background)
		__set_bit(FR_BACKGROUND, &req->flags);

	if (unlikely(req->in.h.uid == ((uid_t)-1) ||
		     req->in.h.gid == ((gid_t)-1))) {
		fuse_put_request(fc, req);
		return ERR_PTR(-EOVERFLOW);
	}
	return req;

 out:
	fuse_drop_waiting(fc);
	return ERR_PTR(err);
}