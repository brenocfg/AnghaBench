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
struct fib6_result {int /*<<< orphan*/  fib6_type; int /*<<< orphan*/  fib6_flags; struct fib6_nh* nh; struct fib6_info* f6i; } ;
struct fib6_nh_frl_arg {int oif; int strict; int* mpri; int* do_rr; struct fib6_nh* nh; int /*<<< orphan*/  flags; } ;
struct fib6_nh {int dummy; } ;
struct fib6_info {scalar_t__ fib6_metric; int /*<<< orphan*/  fib6_type; int /*<<< orphan*/  fib6_flags; struct fib6_nh* fib6_nh; int /*<<< orphan*/  nh; int /*<<< orphan*/  fib6_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTF_REJECT ; 
 int /*<<< orphan*/  RTN_BLACKHOLE ; 
 scalar_t__ fib6_check_expired (struct fib6_info*) ; 
 scalar_t__ find_match (struct fib6_nh*,int /*<<< orphan*/ ,int,int,int*,int*) ; 
 struct fib6_nh* nexthop_fib6_nh (int /*<<< orphan*/ ) ; 
 scalar_t__ nexthop_for_each_fib6_nh (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fib6_nh_frl_arg*) ; 
 scalar_t__ nexthop_is_blackhole (int /*<<< orphan*/ ) ; 
 struct fib6_info* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt6_nh_find_match ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __find_rr_leaf(struct fib6_info *f6i_start,
			   struct fib6_info *nomatch, u32 metric,
			   struct fib6_result *res, struct fib6_info **cont,
			   int oif, int strict, bool *do_rr, int *mpri)
{
	struct fib6_info *f6i;

	for (f6i = f6i_start;
	     f6i && f6i != nomatch;
	     f6i = rcu_dereference(f6i->fib6_next)) {
		bool matched = false;
		struct fib6_nh *nh;

		if (cont && f6i->fib6_metric != metric) {
			*cont = f6i;
			return;
		}

		if (fib6_check_expired(f6i))
			continue;

		if (unlikely(f6i->nh)) {
			struct fib6_nh_frl_arg arg = {
				.flags  = f6i->fib6_flags,
				.oif    = oif,
				.strict = strict,
				.mpri   = mpri,
				.do_rr  = do_rr
			};

			if (nexthop_is_blackhole(f6i->nh)) {
				res->fib6_flags = RTF_REJECT;
				res->fib6_type = RTN_BLACKHOLE;
				res->f6i = f6i;
				res->nh = nexthop_fib6_nh(f6i->nh);
				return;
			}
			if (nexthop_for_each_fib6_nh(f6i->nh, rt6_nh_find_match,
						     &arg)) {
				matched = true;
				nh = arg.nh;
			}
		} else {
			nh = f6i->fib6_nh;
			if (find_match(nh, f6i->fib6_flags, oif, strict,
				       mpri, do_rr))
				matched = true;
		}
		if (matched) {
			res->f6i = f6i;
			res->nh = nh;
			res->fib6_flags = f6i->fib6_flags;
			res->fib6_type = f6i->fib6_type;
		}
	}
}