#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fib6_nh_rd_arg {int /*<<< orphan*/  ret; int /*<<< orphan*/  gw; int /*<<< orphan*/  fl6; TYPE_1__* res; } ;
struct fib6_nh {int dummy; } ;
struct TYPE_2__ {struct fib6_nh* nh; } ;

/* Variables and functions */
 int ip6_redirect_nh_match (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fib6_nh_redirect_match(struct fib6_nh *nh, void *_arg)
{
	struct fib6_nh_rd_arg *arg = _arg;

	arg->res->nh = nh;
	return ip6_redirect_nh_match(arg->res, arg->fl6, arg->gw, arg->ret);
}