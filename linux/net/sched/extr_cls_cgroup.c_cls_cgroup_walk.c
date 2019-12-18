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
struct tcf_walker {scalar_t__ count; scalar_t__ skip; scalar_t__ (* fn ) (struct tcf_proto*,struct cls_cgroup_head*,struct tcf_walker*) ;int stop; } ;
struct tcf_proto {int /*<<< orphan*/  root; } ;
struct cls_cgroup_head {int dummy; } ;

/* Variables and functions */
 struct cls_cgroup_head* rtnl_dereference (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct tcf_proto*,struct cls_cgroup_head*,struct tcf_walker*) ; 

__attribute__((used)) static void cls_cgroup_walk(struct tcf_proto *tp, struct tcf_walker *arg,
			    bool rtnl_held)
{
	struct cls_cgroup_head *head = rtnl_dereference(tp->root);

	if (arg->count < arg->skip)
		goto skip;

	if (!head)
		return;
	if (arg->fn(tp, head, arg) < 0) {
		arg->stop = 1;
		return;
	}
skip:
	arg->count++;
}