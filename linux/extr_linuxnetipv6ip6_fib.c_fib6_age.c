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
struct fib6_info {int fib6_flags; int /*<<< orphan*/  expires; } ;
struct fib6_gc_args {int /*<<< orphan*/  more; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT6_TRACE (char*,struct fib6_info*) ; 
 int RTF_EXPIRES ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  rt6_age_exceptions (struct fib6_info*,struct fib6_gc_args*,unsigned long) ; 
 scalar_t__ time_after (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fib6_age(struct fib6_info *rt, void *arg)
{
	struct fib6_gc_args *gc_args = arg;
	unsigned long now = jiffies;

	/*
	 *	check addrconf expiration here.
	 *	Routes are expired even if they are in use.
	 */

	if (rt->fib6_flags & RTF_EXPIRES && rt->expires) {
		if (time_after(now, rt->expires)) {
			RT6_TRACE("expiring %p\n", rt);
			return -1;
		}
		gc_args->more++;
	}

	/*	Also age clones in the exception table.
	 *	Note, that clones are aged out
	 *	only if they are not in use now.
	 */
	rt6_age_exceptions(rt, gc_args, now);

	return 0;
}