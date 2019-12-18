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
struct TYPE_3__ {int /*<<< orphan*/  timer; } ;
struct io_kiocb {int /*<<< orphan*/  user_data; TYPE_2__* ctx; int /*<<< orphan*/  list; TYPE_1__ timeout; } ;
struct TYPE_4__ {int /*<<< orphan*/  cq_timeouts; } ;

/* Variables and functions */
 int /*<<< orphan*/  __io_free_req (struct io_kiocb*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int hrtimer_try_to_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_cqring_fill_event (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void io_kill_timeout(struct io_kiocb *req)
{
	int ret;

	ret = hrtimer_try_to_cancel(&req->timeout.timer);
	if (ret != -1) {
		atomic_inc(&req->ctx->cq_timeouts);
		list_del(&req->list);
		io_cqring_fill_event(req->ctx, req->user_data, 0);
		__io_free_req(req);
	}
}