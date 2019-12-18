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
struct tcf_proto {int dummy; } ;
struct tcf_chain {int dummy; } ;

/* Variables and functions */
 struct tcf_proto* __tcf_get_next_proto (struct tcf_chain*,struct tcf_proto*) ; 
 int /*<<< orphan*/  tcf_proto_put (struct tcf_proto*,int,int /*<<< orphan*/ *) ; 

struct tcf_proto *
tcf_get_next_proto(struct tcf_chain *chain, struct tcf_proto *tp,
		   bool rtnl_held)
{
	struct tcf_proto *tp_next = __tcf_get_next_proto(chain, tp);

	if (tp)
		tcf_proto_put(tp, rtnl_held, NULL);

	return tp_next;
}