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
struct TYPE_2__ {int nh_flags; } ;
struct fib6_info {TYPE_1__ fib6_nh; } ;

/* Variables and functions */
 int RT6_LOOKUP_F_IGNORE_LINKSTATE ; 
 int RT6_LOOKUP_F_REACHABLE ; 
 int RT6_NUD_FAIL_DO_RR ; 
 int RT6_NUD_FAIL_HARD ; 
 int RTNH_F_DEAD ; 
 int RTNH_F_LINKDOWN ; 
 scalar_t__ fib6_check_expired (struct fib6_info*) ; 
 scalar_t__ fib6_ignore_linkdown (struct fib6_info*) ; 
 int /*<<< orphan*/  rt6_probe (struct fib6_info*) ; 
 int rt6_score_route (struct fib6_info*,int,int) ; 

__attribute__((used)) static struct fib6_info *find_match(struct fib6_info *rt, int oif, int strict,
				   int *mpri, struct fib6_info *match,
				   bool *do_rr)
{
	int m;
	bool match_do_rr = false;

	if (rt->fib6_nh.nh_flags & RTNH_F_DEAD)
		goto out;

	if (fib6_ignore_linkdown(rt) &&
	    rt->fib6_nh.nh_flags & RTNH_F_LINKDOWN &&
	    !(strict & RT6_LOOKUP_F_IGNORE_LINKSTATE))
		goto out;

	if (fib6_check_expired(rt))
		goto out;

	m = rt6_score_route(rt, oif, strict);
	if (m == RT6_NUD_FAIL_DO_RR) {
		match_do_rr = true;
		m = 0; /* lowest valid score */
	} else if (m == RT6_NUD_FAIL_HARD) {
		goto out;
	}

	if (strict & RT6_LOOKUP_F_REACHABLE)
		rt6_probe(rt);

	/* note that m can be RT6_NUD_FAIL_PROBE at this point */
	if (m > *mpri) {
		*do_rr = match_do_rr;
		*mpri = m;
		match = rt;
	}
out:
	return match;
}