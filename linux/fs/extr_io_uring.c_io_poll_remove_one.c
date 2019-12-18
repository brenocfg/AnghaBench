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
struct TYPE_3__ {int /*<<< orphan*/  entry; } ;
struct io_poll_iocb {TYPE_2__* head; TYPE_1__ wait; int /*<<< orphan*/  canceled; } ;
struct io_kiocb {int /*<<< orphan*/  list; int /*<<< orphan*/  ctx; struct io_poll_iocb poll; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  io_queue_async_work (int /*<<< orphan*/ ,struct io_kiocb*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void io_poll_remove_one(struct io_kiocb *req)
{
	struct io_poll_iocb *poll = &req->poll;

	spin_lock(&poll->head->lock);
	WRITE_ONCE(poll->canceled, true);
	if (!list_empty(&poll->wait.entry)) {
		list_del_init(&poll->wait.entry);
		io_queue_async_work(req->ctx, req);
	}
	spin_unlock(&poll->head->lock);

	list_del_init(&req->list);
}