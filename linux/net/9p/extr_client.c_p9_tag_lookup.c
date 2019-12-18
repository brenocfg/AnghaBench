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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ tag; } ;
struct p9_req_t {TYPE_1__ tc; } ;
struct p9_client {int /*<<< orphan*/  reqs; } ;

/* Variables and functions */
 struct p9_req_t* idr_find (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  p9_req_put (struct p9_req_t*) ; 
 int /*<<< orphan*/  p9_req_try_get (struct p9_req_t*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct p9_req_t *p9_tag_lookup(struct p9_client *c, u16 tag)
{
	struct p9_req_t *req;

	rcu_read_lock();
again:
	req = idr_find(&c->reqs, tag);
	if (req) {
		/* We have to be careful with the req found under rcu_read_lock
		 * Thanks to SLAB_TYPESAFE_BY_RCU we can safely try to get the
		 * ref again without corrupting other data, then check again
		 * that the tag matches once we have the ref
		 */
		if (!p9_req_try_get(req))
			goto again;
		if (req->tc.tag != tag) {
			p9_req_put(req);
			goto again;
		}
	}
	rcu_read_unlock();

	return req;
}