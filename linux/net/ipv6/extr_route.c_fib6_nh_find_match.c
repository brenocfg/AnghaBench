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
struct fib6_nh_match_arg {scalar_t__ dev; struct fib6_nh* match; scalar_t__ gw; } ;
struct fib6_nh {scalar_t__ fib_nh_dev; int /*<<< orphan*/  fib_nh_gw6; scalar_t__ fib_nh_gw_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipv6_addr_equal (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fib6_nh_find_match(struct fib6_nh *nh, void *_arg)
{
	struct fib6_nh_match_arg *arg = _arg;

	if (arg->dev != nh->fib_nh_dev ||
	    (arg->gw && !nh->fib_nh_gw_family) ||
	    (!arg->gw && nh->fib_nh_gw_family) ||
	    (arg->gw && !ipv6_addr_equal(arg->gw, &nh->fib_nh_gw6)))
		return 0;

	arg->match = nh;

	/* found a match, break the loop */
	return 1;
}