#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct fuse_poll_out {int /*<<< orphan*/  revents; } ;
struct fuse_poll_in {int /*<<< orphan*/  flags; int /*<<< orphan*/  events; int /*<<< orphan*/  kh; int /*<<< orphan*/  fh; } ;
struct fuse_file {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  poll_wait; int /*<<< orphan*/  kh; int /*<<< orphan*/  fh; struct fuse_conn* fc; } ;
struct fuse_conn {int no_poll; } ;
struct file {struct fuse_file* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  outarg ;
typedef  int /*<<< orphan*/  inarg ;
typedef  int /*<<< orphan*/  __poll_t ;
struct TYPE_8__ {int in_numargs; int out_numargs; TYPE_2__* out_args; TYPE_1__* in_args; int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_7__ {int size; struct fuse_poll_out* value; } ;
struct TYPE_6__ {int size; struct fuse_poll_in* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_POLLMASK ; 
 int ENOSYS ; 
 int /*<<< orphan*/  EPOLLERR ; 
 int /*<<< orphan*/  FUSE_ARGS (TYPE_3__) ; 
 int /*<<< orphan*/  FUSE_POLL ; 
 int /*<<< orphan*/  FUSE_POLL_SCHEDULE_NOTIFY ; 
 TYPE_3__ args ; 
 int /*<<< orphan*/  demangle_poll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_register_polled_file (struct fuse_conn*,struct fuse_file*) ; 
 int fuse_simple_request (struct fuse_conn*,TYPE_3__*) ; 
 int /*<<< orphan*/  mangle_poll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poll_requested_events (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 

__poll_t fuse_file_poll(struct file *file, poll_table *wait)
{
	struct fuse_file *ff = file->private_data;
	struct fuse_conn *fc = ff->fc;
	struct fuse_poll_in inarg = { .fh = ff->fh, .kh = ff->kh };
	struct fuse_poll_out outarg;
	FUSE_ARGS(args);
	int err;

	if (fc->no_poll)
		return DEFAULT_POLLMASK;

	poll_wait(file, &ff->poll_wait, wait);
	inarg.events = mangle_poll(poll_requested_events(wait));

	/*
	 * Ask for notification iff there's someone waiting for it.
	 * The client may ignore the flag and always notify.
	 */
	if (waitqueue_active(&ff->poll_wait)) {
		inarg.flags |= FUSE_POLL_SCHEDULE_NOTIFY;
		fuse_register_polled_file(fc, ff);
	}

	args.opcode = FUSE_POLL;
	args.nodeid = ff->nodeid;
	args.in_numargs = 1;
	args.in_args[0].size = sizeof(inarg);
	args.in_args[0].value = &inarg;
	args.out_numargs = 1;
	args.out_args[0].size = sizeof(outarg);
	args.out_args[0].value = &outarg;
	err = fuse_simple_request(fc, &args);

	if (!err)
		return demangle_poll(outarg.revents);
	if (err == -ENOSYS) {
		fc->no_poll = 1;
		return DEFAULT_POLLMASK;
	}
	return EPOLLERR;
}