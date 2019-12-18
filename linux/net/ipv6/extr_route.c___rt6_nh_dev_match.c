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
struct fib6_nh_dm_arg {int /*<<< orphan*/  flags; int /*<<< orphan*/  oif; int /*<<< orphan*/  saddr; int /*<<< orphan*/  net; struct fib6_nh* nh; } ;
struct fib6_nh {int dummy; } ;

/* Variables and functions */
 int __rt6_device_match (int /*<<< orphan*/ ,struct fib6_nh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __rt6_nh_dev_match(struct fib6_nh *nh, void *_arg)
{
	struct fib6_nh_dm_arg *arg = _arg;

	arg->nh = nh;
	return __rt6_device_match(arg->net, nh, arg->saddr, arg->oif,
				  arg->flags);
}