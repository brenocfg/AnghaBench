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
struct fib6_table {int dummy; } ;
struct fib6_nh_pcpu_arg {struct fib6_table const* table; struct fib6_info* from; } ;
struct fib6_nh {int dummy; } ;
struct fib6_info {int fib6_destroying; struct fib6_nh* fib6_nh; scalar_t__ nh; } ;

/* Variables and functions */
 int /*<<< orphan*/  __fib6_drop_pcpu_from (struct fib6_nh*,struct fib6_info*,struct fib6_table const*) ; 
 int /*<<< orphan*/  fib6_nh_drop_pcpu_from ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  nexthop_for_each_fib6_nh (scalar_t__,int /*<<< orphan*/ ,struct fib6_nh_pcpu_arg*) ; 

__attribute__((used)) static void fib6_drop_pcpu_from(struct fib6_info *f6i,
				const struct fib6_table *table)
{
	/* Make sure rt6_make_pcpu_route() wont add other percpu routes
	 * while we are cleaning them here.
	 */
	f6i->fib6_destroying = 1;
	mb(); /* paired with the cmpxchg() in rt6_make_pcpu_route() */

	if (f6i->nh) {
		struct fib6_nh_pcpu_arg arg = {
			.from = f6i,
			.table = table
		};

		nexthop_for_each_fib6_nh(f6i->nh, fib6_nh_drop_pcpu_from,
					 &arg);
	} else {
		struct fib6_nh *fib6_nh;

		fib6_nh = f6i->fib6_nh;
		__fib6_drop_pcpu_from(fib6_nh, f6i, table);
	}
}