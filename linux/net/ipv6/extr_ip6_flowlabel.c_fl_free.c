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
struct ip6_flowlabel {int /*<<< orphan*/  rcu; scalar_t__ opt; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fl_free_rcu ; 
 scalar_t__ fl_shared_exclusive (struct ip6_flowlabel*) ; 
 int /*<<< orphan*/  ipv6_flowlabel_exclusive ; 
 int /*<<< orphan*/  static_branch_slow_dec_deferred (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fl_free(struct ip6_flowlabel *fl)
{
	if (!fl)
		return;

	if (fl_shared_exclusive(fl) || fl->opt)
		static_branch_slow_dec_deferred(&ipv6_flowlabel_exclusive);

	call_rcu(&fl->rcu, fl_free_rcu);
}