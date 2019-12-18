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
struct fib6_nh_age_excptn_arg {unsigned long now; struct fib6_gc_args* gc_args; } ;
struct fib6_info {int /*<<< orphan*/  fib6_nh; scalar_t__ nh; } ;
struct fib6_gc_args {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fib6_nh_age_exceptions (int /*<<< orphan*/ ,struct fib6_gc_args*,unsigned long) ; 
 int /*<<< orphan*/  nexthop_for_each_fib6_nh (scalar_t__,int /*<<< orphan*/ ,struct fib6_nh_age_excptn_arg*) ; 
 int /*<<< orphan*/  rt6_nh_age_exceptions ; 

void rt6_age_exceptions(struct fib6_info *f6i,
			struct fib6_gc_args *gc_args,
			unsigned long now)
{
	if (f6i->nh) {
		struct fib6_nh_age_excptn_arg arg = {
			.gc_args = gc_args,
			.now = now
		};

		nexthop_for_each_fib6_nh(f6i->nh, rt6_nh_age_exceptions,
					 &arg);
	} else {
		fib6_nh_age_exceptions(f6i->fib6_nh, gc_args, now);
	}
}