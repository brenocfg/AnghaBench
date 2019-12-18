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
struct fib6_nh_age_excptn_arg {int /*<<< orphan*/  now; int /*<<< orphan*/  gc_args; } ;
struct fib6_nh {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fib6_nh_age_exceptions (struct fib6_nh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt6_nh_age_exceptions(struct fib6_nh *nh, void *_arg)
{
	struct fib6_nh_age_excptn_arg *arg = _arg;

	fib6_nh_age_exceptions(nh, arg->gc_args, arg->now);
	return 0;
}