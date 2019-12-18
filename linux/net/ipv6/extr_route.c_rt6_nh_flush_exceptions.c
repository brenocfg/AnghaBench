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
struct fib6_nh {int dummy; } ;
struct fib6_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fib6_nh_flush_exceptions (struct fib6_nh*,struct fib6_info*) ; 

__attribute__((used)) static int rt6_nh_flush_exceptions(struct fib6_nh *nh, void *arg)
{
	struct fib6_info *f6i = arg;

	fib6_nh_flush_exceptions(nh, f6i);

	return 0;
}