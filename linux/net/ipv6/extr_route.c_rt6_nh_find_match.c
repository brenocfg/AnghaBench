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
struct fib6_nh_frl_arg {int /*<<< orphan*/  do_rr; int /*<<< orphan*/  mpri; int /*<<< orphan*/  strict; int /*<<< orphan*/  oif; int /*<<< orphan*/  flags; struct fib6_nh* nh; } ;
struct fib6_nh {int dummy; } ;

/* Variables and functions */
 int find_match (struct fib6_nh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt6_nh_find_match(struct fib6_nh *nh, void *_arg)
{
	struct fib6_nh_frl_arg *arg = _arg;

	arg->nh = nh;
	return find_match(nh, arg->flags, arg->oif, arg->strict,
			  arg->mpri, arg->do_rr);
}