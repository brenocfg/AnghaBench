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
struct TYPE_3__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct TYPE_4__ {TYPE_1__ h; } ;
struct fuse_req {int /*<<< orphan*/  flags; TYPE_2__ in; } ;
struct fuse_conn {int /*<<< orphan*/  pid_ns; int /*<<< orphan*/  user_ns; int /*<<< orphan*/  initialized; int /*<<< orphan*/  blocked_waitq; int /*<<< orphan*/  num_waiting; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FR_BACKGROUND ; 
 int /*<<< orphan*/  FR_WAITING ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  from_kgid_munged (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kuid_munged (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fuse_req* fuse_request_alloc (int /*<<< orphan*/ ) ; 
 struct fuse_req* get_reserved_req (struct fuse_conn*,struct file*) ; 
 int /*<<< orphan*/  pid_nr_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  task_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct fuse_req *fuse_get_req_nofail_nopages(struct fuse_conn *fc,
					     struct file *file)
{
	struct fuse_req *req;

	atomic_inc(&fc->num_waiting);
	wait_event(fc->blocked_waitq, fc->initialized);
	/* Matches smp_wmb() in fuse_set_initialized() */
	smp_rmb();
	req = fuse_request_alloc(0);
	if (!req)
		req = get_reserved_req(fc, file);

	req->in.h.uid = from_kuid_munged(fc->user_ns, current_fsuid());
	req->in.h.gid = from_kgid_munged(fc->user_ns, current_fsgid());
	req->in.h.pid = pid_nr_ns(task_pid(current), fc->pid_ns);

	__set_bit(FR_WAITING, &req->flags);
	__clear_bit(FR_BACKGROUND, &req->flags);
	return req;
}