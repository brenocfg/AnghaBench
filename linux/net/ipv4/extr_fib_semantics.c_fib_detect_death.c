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
struct neighbour {int nud_state; } ;
struct TYPE_3__ {int /*<<< orphan*/  ipv6; int /*<<< orphan*/  ipv4; } ;
struct fib_nh_common {scalar_t__ nhc_gw_family; int /*<<< orphan*/  nhc_dev; TYPE_1__ nhc_gw; } ;
struct fib_info {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * nd_tbl; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int NUD_INCOMPLETE ; 
 int NUD_NONE ; 
 int NUD_REACHABLE ; 
 int NUD_VALID ; 
 int /*<<< orphan*/  arp_tbl ; 
 struct fib_nh_common* fib_info_nhc (struct fib_info*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ipv6_stub ; 
 scalar_t__ likely (int) ; 
 struct neighbour* neigh_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 

__attribute__((used)) static int fib_detect_death(struct fib_info *fi, int order,
			    struct fib_info **last_resort, int *last_idx,
			    int dflt)
{
	const struct fib_nh_common *nhc = fib_info_nhc(fi, 0);
	struct neighbour *n;
	int state = NUD_NONE;

	if (likely(nhc->nhc_gw_family == AF_INET))
		n = neigh_lookup(&arp_tbl, &nhc->nhc_gw.ipv4, nhc->nhc_dev);
	else if (nhc->nhc_gw_family == AF_INET6)
		n = neigh_lookup(ipv6_stub->nd_tbl, &nhc->nhc_gw.ipv6,
				 nhc->nhc_dev);
	else
		n = NULL;

	if (n) {
		state = n->nud_state;
		neigh_release(n);
	} else {
		return 0;
	}
	if (state == NUD_REACHABLE)
		return 0;
	if ((state & NUD_VALID) && order != dflt)
		return 0;
	if ((state & NUD_VALID) ||
	    (*last_idx < 0 && order > dflt && state != NUD_INCOMPLETE)) {
		*last_resort = fi;
		*last_idx = order;
	}
	return 1;
}