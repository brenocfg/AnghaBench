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
struct p9_conn {scalar_t__ err; int /*<<< orphan*/  wq; int /*<<< orphan*/  wsched; int /*<<< orphan*/  client; int /*<<< orphan*/  unsent_req_list; } ;
struct p9_trans_fd {struct p9_conn conn; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct p9_req_t {int /*<<< orphan*/  req_list; int /*<<< orphan*/  status; TYPE_1__ tc; } ;
struct p9_client {int /*<<< orphan*/  lock; struct p9_trans_fd* trans; } ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLOUT ; 
 int /*<<< orphan*/  P9_DEBUG_TRANS ; 
 int /*<<< orphan*/  REQ_STATUS_UNSENT ; 
 int /*<<< orphan*/  Wpending ; 
 int /*<<< orphan*/  Wworksched ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,struct p9_conn*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int p9_fd_poll (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int p9_fd_request(struct p9_client *client, struct p9_req_t *req)
{
	__poll_t n;
	struct p9_trans_fd *ts = client->trans;
	struct p9_conn *m = &ts->conn;

	p9_debug(P9_DEBUG_TRANS, "mux %p task %p tcall %p id %d\n",
		 m, current, &req->tc, req->tc.id);
	if (m->err < 0)
		return m->err;

	spin_lock(&client->lock);
	req->status = REQ_STATUS_UNSENT;
	list_add_tail(&req->req_list, &m->unsent_req_list);
	spin_unlock(&client->lock);

	if (test_and_clear_bit(Wpending, &m->wsched))
		n = EPOLLOUT;
	else
		n = p9_fd_poll(m->client, NULL, NULL);

	if (n & EPOLLOUT && !test_and_set_bit(Wworksched, &m->wsched))
		schedule_work(&m->wq);

	return 0;
}