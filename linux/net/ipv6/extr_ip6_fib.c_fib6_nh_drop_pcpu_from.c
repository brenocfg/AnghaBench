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
struct fib6_nh_pcpu_arg {int /*<<< orphan*/  table; int /*<<< orphan*/  from; } ;
struct fib6_nh {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __fib6_drop_pcpu_from (struct fib6_nh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fib6_nh_drop_pcpu_from(struct fib6_nh *nh, void *_arg)
{
	struct fib6_nh_pcpu_arg *arg = _arg;

	__fib6_drop_pcpu_from(nh, arg->from, arg->table);
	return 0;
}