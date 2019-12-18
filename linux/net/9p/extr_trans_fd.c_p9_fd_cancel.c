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
struct p9_req_t {scalar_t__ status; int /*<<< orphan*/  req_list; } ;
struct p9_client {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_TRANS ; 
 scalar_t__ REQ_STATUS_FLSHD ; 
 scalar_t__ REQ_STATUS_UNSENT ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,struct p9_client*,struct p9_req_t*) ; 
 int /*<<< orphan*/  p9_req_put (struct p9_req_t*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int p9_fd_cancel(struct p9_client *client, struct p9_req_t *req)
{
	int ret = 1;

	p9_debug(P9_DEBUG_TRANS, "client %p req %p\n", client, req);

	spin_lock(&client->lock);

	if (req->status == REQ_STATUS_UNSENT) {
		list_del(&req->req_list);
		req->status = REQ_STATUS_FLSHD;
		p9_req_put(req);
		ret = 0;
	}
	spin_unlock(&client->lock);

	return ret;
}