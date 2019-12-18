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
struct neighbour {int nud_state; } ;
struct fib6_nh {int /*<<< orphan*/  fib_nh_gw6; int /*<<< orphan*/  fib_nh_dev; } ;

/* Variables and functions */
 int NUD_REACHABLE ; 
 int NUD_VALID ; 
 struct neighbour* __ipv6_neigh_lookup_noref_stub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 

__attribute__((used)) static bool ipv6_good_nh(const struct fib6_nh *nh)
{
	int state = NUD_REACHABLE;
	struct neighbour *n;

	rcu_read_lock_bh();

	n = __ipv6_neigh_lookup_noref_stub(nh->fib_nh_dev, &nh->fib_nh_gw6);
	if (n)
		state = n->nud_state;

	rcu_read_unlock_bh();

	return !!(state & NUD_VALID);
}