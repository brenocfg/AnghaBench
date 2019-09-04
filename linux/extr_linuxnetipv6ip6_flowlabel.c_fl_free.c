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
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;
struct ip6_flowlabel {scalar_t__ share; int /*<<< orphan*/  opt; TYPE_1__ owner; } ;

/* Variables and functions */
 scalar_t__ IPV6_FL_S_PROCESS ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_rcu (struct ip6_flowlabel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 

__attribute__((used)) static void fl_free(struct ip6_flowlabel *fl)
{
	if (fl) {
		if (fl->share == IPV6_FL_S_PROCESS)
			put_pid(fl->owner.pid);
		kfree(fl->opt);
		kfree_rcu(fl, rcu);
	}
}