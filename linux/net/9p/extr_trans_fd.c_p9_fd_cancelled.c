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
struct p9_req_t {int /*<<< orphan*/  req_list; } ;
struct p9_client {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_TRANS ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,struct p9_client*,struct p9_req_t*) ; 
 int /*<<< orphan*/  p9_req_put (struct p9_req_t*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int p9_fd_cancelled(struct p9_client *client, struct p9_req_t *req)
{
	p9_debug(P9_DEBUG_TRANS, "client %p req %p\n", client, req);

	/* we haven't received a response for oldreq,
	 * remove it from the list.
	 */
	spin_lock(&client->lock);
	list_del(&req->req_list);
	spin_unlock(&client->lock);
	p9_req_put(req);

	return 0;
}