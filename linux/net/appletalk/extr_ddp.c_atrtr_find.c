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
struct TYPE_2__ {scalar_t__ s_net; scalar_t__ s_node; } ;
struct atalk_route {int flags; scalar_t__ dev; TYPE_1__ target; struct atalk_route* next; } ;
struct atalk_addr {scalar_t__ s_net; scalar_t__ s_node; } ;

/* Variables and functions */
 int RTF_HOST ; 
 int RTF_UP ; 
 struct atalk_route* atalk_routes ; 
 int /*<<< orphan*/  atalk_routes_lock ; 
 struct atalk_route atrtr_default ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct atalk_route *atrtr_find(struct atalk_addr *target)
{
	/*
	 * we must search through all routes unless we find a
	 * host route, because some host routes might overlap
	 * network routes
	 */
	struct atalk_route *net_route = NULL;
	struct atalk_route *r;

	read_lock_bh(&atalk_routes_lock);
	for (r = atalk_routes; r; r = r->next) {
		if (!(r->flags & RTF_UP))
			continue;

		if (r->target.s_net == target->s_net) {
			if (r->flags & RTF_HOST) {
				/*
				 * if this host route is for the target,
				 * the we're done
				 */
				if (r->target.s_node == target->s_node)
					goto out;
			} else
				/*
				 * this route will work if there isn't a
				 * direct host route, so cache it
				 */
				net_route = r;
		}
	}

	/*
	 * if we found a network route but not a direct host
	 * route, then return it
	 */
	if (net_route)
		r = net_route;
	else if (atrtr_default.dev)
		r = &atrtr_default;
	else /* No route can be found */
		r = NULL;
out:
	read_unlock_bh(&atalk_routes_lock);
	return r;
}