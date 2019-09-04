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
struct neighbour {int nud_state; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  nh_gw; int /*<<< orphan*/  nh_dev; } ;
struct fib6_info {int fib6_flags; TYPE_1__ fib6_nh; } ;
typedef  enum rt6_nud_state { ____Placeholder_rt6_nud_state } rt6_nud_state ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_IPV6_ROUTER_PREF ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int NUD_VALID ; 
 int RT6_NUD_FAIL_DO_RR ; 
 int RT6_NUD_FAIL_HARD ; 
 int RT6_NUD_SUCCEED ; 
 int RTF_GATEWAY ; 
 int RTF_NONEXTHOP ; 
 struct neighbour* __ipv6_neigh_lookup_noref (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline enum rt6_nud_state rt6_check_neigh(struct fib6_info *rt)
{
	enum rt6_nud_state ret = RT6_NUD_FAIL_HARD;
	struct neighbour *neigh;

	if (rt->fib6_flags & RTF_NONEXTHOP ||
	    !(rt->fib6_flags & RTF_GATEWAY))
		return RT6_NUD_SUCCEED;

	rcu_read_lock_bh();
	neigh = __ipv6_neigh_lookup_noref(rt->fib6_nh.nh_dev,
					  &rt->fib6_nh.nh_gw);
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