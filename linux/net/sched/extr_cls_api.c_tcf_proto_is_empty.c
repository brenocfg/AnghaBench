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
struct tcf_walker {int /*<<< orphan*/  nonempty; int /*<<< orphan*/  fn; } ;
struct tcf_proto {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* walk ) (struct tcf_proto*,struct tcf_walker*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct tcf_proto*,struct tcf_walker*,int) ; 
 int /*<<< orphan*/  walker_check_empty ; 

__attribute__((used)) static bool tcf_proto_is_empty(struct tcf_proto *tp, bool rtnl_held)
{
	struct tcf_walker walker = { .fn = walker_check_empty, };

	if (tp->ops->walk) {
		tp->ops->walk(tp, &walker, rtnl_held);
		return !walker.nonempty;
	}
	return true;
}