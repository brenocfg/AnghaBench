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
struct TYPE_3__ {scalar_t__ len; } ;
struct TYPE_4__ {scalar_t__ args; int /*<<< orphan*/  numargs; TYPE_1__ h; } ;
struct fuse_req {int /*<<< orphan*/  list; TYPE_2__ in; } ;
struct fuse_iqueue {int /*<<< orphan*/  fasync; int /*<<< orphan*/  waitq; int /*<<< orphan*/  pending; } ;
struct fuse_in_header {int dummy; } ;
struct fuse_arg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ len_args (int /*<<< orphan*/ ,struct fuse_arg*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void queue_request(struct fuse_iqueue *fiq, struct fuse_req *req)
{
	req->in.h.len = sizeof(struct fuse_in_header) +
		len_args(req->in.numargs, (struct fuse_arg *) req->in.args);
	list_add_tail(&req->list, &fiq->pending);
	wake_up_locked(&fiq->waitq);
	kill_fasync(&fiq->fasync, SIGIO, POLL_IN);
}