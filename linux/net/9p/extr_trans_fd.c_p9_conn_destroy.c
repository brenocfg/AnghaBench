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
struct TYPE_2__ {int /*<<< orphan*/  next; int /*<<< orphan*/  prev; } ;
struct p9_conn {int /*<<< orphan*/ * client; int /*<<< orphan*/ * wreq; int /*<<< orphan*/  wq; int /*<<< orphan*/ * rreq; int /*<<< orphan*/  rq; TYPE_1__ mux_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  P9_DEBUG_TRANS ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p9_conn_cancel (struct p9_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,struct p9_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p9_mux_poll_stop (struct p9_conn*) ; 
 int /*<<< orphan*/  p9_req_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void p9_conn_destroy(struct p9_conn *m)
{
	p9_debug(P9_DEBUG_TRANS, "mux %p prev %p next %p\n",
		 m, m->mux_list.prev, m->mux_list.next);

	p9_mux_poll_stop(m);
	cancel_work_sync(&m->rq);
	if (m->rreq) {
		p9_req_put(m->rreq);
		m->rreq = NULL;
	}
	cancel_work_sync(&m->wq);
	if (m->wreq) {
		p9_req_put(m->wreq);
		m->wreq = NULL;
	}

	p9_conn_cancel(m, -ECONNRESET);

	m->client = NULL;
}