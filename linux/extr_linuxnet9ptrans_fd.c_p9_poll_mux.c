#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct p9_conn {scalar_t__ err; int /*<<< orphan*/  wq; int /*<<< orphan*/  wsched; int /*<<< orphan*/  unsent_req_list; scalar_t__ wsize; int /*<<< orphan*/  rq; int /*<<< orphan*/  client; } ;
typedef  int __poll_t ;

/* Variables and functions */
 int ECONNRESET ; 
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLNVAL ; 
 int EPOLLOUT ; 
 int /*<<< orphan*/  P9_DEBUG_TRANS ; 
 int /*<<< orphan*/  Rpending ; 
 int /*<<< orphan*/  Rworksched ; 
 int /*<<< orphan*/  Wpending ; 
 int /*<<< orphan*/  Wworksched ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p9_conn_cancel (struct p9_conn*,int) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,struct p9_conn*,...) ; 
 int p9_fd_poll (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void p9_poll_mux(struct p9_conn *m)
{
	__poll_t n;
	int err = -ECONNRESET;

	if (m->err < 0)
		return;

	n = p9_fd_poll(m->client, NULL, &err);
	if (n & (EPOLLERR | EPOLLHUP | EPOLLNVAL)) {
		p9_debug(P9_DEBUG_TRANS, "error mux %p err %d\n", m, n);
		p9_conn_cancel(m, err);
	}

	if (n & EPOLLIN) {
		set_bit(Rpending, &m->wsched);
		p9_debug(P9_DEBUG_TRANS, "mux %p can read\n", m);
		if (!test_and_set_bit(Rworksched, &m->wsched)) {
			p9_debug(P9_DEBUG_TRANS, "sched read work %p\n", m);
			schedule_work(&m->rq);
		}
	}

	if (n & EPOLLOUT) {
		set_bit(Wpending, &m->wsched);
		p9_debug(P9_DEBUG_TRANS, "mux %p can write\n", m);
		if ((m->wsize || !list_empty(&m->unsent_req_list)) &&
		    !test_and_set_bit(Wworksched, &m->wsched)) {
			p9_debug(P9_DEBUG_TRANS, "sched write work %p\n", m);
			schedule_work(&m->wq);
		}
	}
}