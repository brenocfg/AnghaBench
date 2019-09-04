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
typedef  scalar_t__ u32 ;
struct fib6_node {int dummy; } ;
struct fib6_info {scalar_t__ fib6_metric; int /*<<< orphan*/  fib6_next; } ;

/* Variables and functions */
 struct fib6_info* find_match (struct fib6_info*,int,int,int*,struct fib6_info*,int*) ; 
 struct fib6_info* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fib6_info *find_rr_leaf(struct fib6_node *fn,
				     struct fib6_info *leaf,
				     struct fib6_info *rr_head,
				     u32 metric, int oif, int strict,
				     bool *do_rr)
{
	struct fib6_info *rt, *match, *cont;
	int mpri = -1;

	match = NULL;
	cont = NULL;
	for (rt = rr_head; rt; rt = rcu_dereference(rt->fib6_next)) {
		if (rt->fib6_metric != metric) {
			cont = rt;
			break;
		}

		match = find_match(rt, oif, strict, &mpri, match, do_rr);
	}

	for (rt = leaf; rt && rt != rr_head;
	     rt = rcu_dereference(rt->fib6_next)) {
		if (rt->fib6_metric != metric) {
			cont = rt;
			break;
		}

		match = find_match(rt, oif, strict, &mpri, match, do_rr);
	}

	if (match || !cont)
		return match;

	for (rt = cont; rt; rt = rcu_dereference(rt->fib6_next))
		match = find_match(rt, oif, strict, &mpri, match, do_rr);

	return match;
}