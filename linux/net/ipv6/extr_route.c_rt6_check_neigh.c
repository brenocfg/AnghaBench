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
struct neighbour {int nud_state; int /*<<< orphan*/  lock; } ;
struct fib6_nh {int /*<<< orphan*/  fib_nh_gw6; int /*<<< orphan*/  fib_nh_dev; } ;
typedef  enum rt6_nud_state { ____Placeholder_rt6_nud_state } rt6_nud_state ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_IPV6_ROUTER_PREF ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int NUD_FAILED ; 
 int NUD_VALID ; 
 int RT6_NUD_FAIL_DO_RR ; 
 int RT6_NUD_FAIL_HARD ; 
 int RT6_NUD_FAIL_PROBE ; 
 int RT6_NUD_SUCCEED ; 
 struct neighbour* __ipv6_neigh_lookup_noref (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum rt6_nud_state rt6_check_neigh(const struct fib6_nh *fib6_nh)
{
	enum rt6_nud_state ret = RT6_NUD_FAIL_HARD;
	struct neighbour *neigh;

	rcu_read_lock_bh();
	neigh = __ipv6_neigh_lookup_noref(fib6_nh->fib_nh_dev,
					  &fib6_nh->fib_nh_gw6);
	if (neigh) {
		read_lock(&neigh->lock);
		if (neigh->nud_state & NUD_VALID)
			ret = RT6_NUD_SUCCEED;
#ifdef CONFIG_IPV6_ROUTER_PREF
		else if (!(neigh->nud_state & NUD_FAILED))
			ret = RT6_NUD_SUCCEED;
		else
			ret = RT6_NUD_FAIL_PROBE;
#endif
		read_unlock(&neigh->lock);
	} else {
		ret = IS_ENABLED(CONFIG_IPV6_ROUTER_PREF) ?
		      RT6_NUD_SUCCEED : RT6_NUD_FAIL_DO_RR;
	}
	rcu_read_unlock_bh();

	return ret;
}