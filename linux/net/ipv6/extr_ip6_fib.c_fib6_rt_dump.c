#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fib6_info {int dummy; } ;
struct fib6_dump_arg {TYPE_2__* net; int /*<<< orphan*/  nb; } ;
struct TYPE_3__ {struct fib6_info* fib6_null_entry; } ;
struct TYPE_4__ {TYPE_1__ ipv6; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIB_EVENT_ENTRY_ADD ; 
 int /*<<< orphan*/  call_fib6_entry_notifier (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,struct fib6_info*) ; 

__attribute__((used)) static void fib6_rt_dump(struct fib6_info *rt, struct fib6_dump_arg *arg)
{
	if (rt == arg->net->ipv6.fib6_null_entry)
		return;
	call_fib6_entry_notifier(arg->nb, arg->net, FIB_EVENT_ENTRY_ADD, rt);
}