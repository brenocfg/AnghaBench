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
struct TYPE_2__ {int /*<<< orphan*/  err; } ;
struct linger_work {TYPE_1__ error; } ;
struct ceph_osd_linger_request {int /*<<< orphan*/  last_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_watch_error ; 
 struct linger_work* lwork_alloc (struct ceph_osd_linger_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lwork_queue (struct linger_work*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void queue_watch_error(struct ceph_osd_linger_request *lreq)
{
	struct linger_work *lwork;

	lwork = lwork_alloc(lreq, do_watch_error);
	if (!lwork) {
		pr_err("failed to allocate error-lwork\n");
		return;
	}

	lwork->error.err = lreq->last_error;
	lwork_queue(lwork);
}