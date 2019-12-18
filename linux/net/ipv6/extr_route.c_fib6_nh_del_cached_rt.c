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
struct fib6_nh_del_cached_rt_arg {int /*<<< orphan*/  f6i; int /*<<< orphan*/  cfg; } ;
struct fib6_nh {int dummy; } ;

/* Variables and functions */
 int ESRCH ; 
 int ip6_del_cached_rt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fib6_nh*) ; 

__attribute__((used)) static int fib6_nh_del_cached_rt(struct fib6_nh *nh, void *_arg)
{
	struct fib6_nh_del_cached_rt_arg *arg = _arg;
	int rc;

	rc = ip6_del_cached_rt(arg->cfg, arg->f6i, nh);
	return rc != -ESRCH ? rc : 0;
}