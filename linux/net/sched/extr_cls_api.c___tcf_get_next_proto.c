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
typedef  scalar_t__ u32 ;
struct tcf_proto {scalar_t__ prio; int /*<<< orphan*/  next; int /*<<< orphan*/  deleting; } ;
struct tcf_chain {int /*<<< orphan*/  filter_chain_lock; int /*<<< orphan*/  filter_chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct tcf_proto* tcf_chain_dereference (int /*<<< orphan*/ ,struct tcf_chain*) ; 
 int /*<<< orphan*/  tcf_proto_get (struct tcf_proto*) ; 
 scalar_t__ tcf_proto_is_deleting (struct tcf_proto*) ; 

__attribute__((used)) static struct tcf_proto *
__tcf_get_next_proto(struct tcf_chain *chain, struct tcf_proto *tp)
{
	u32 prio = 0;

	ASSERT_RTNL();
	mutex_lock(&chain->filter_chain_lock);

	if (!tp) {
		tp = tcf_chain_dereference(chain->filter_chain, chain);
	} else if (tcf_proto_is_deleting(tp)) {
		/* 'deleting' flag is set and chain->filter_chain_lock was
		 * unlocked, which means next pointer could be invalid. Restart
		 * search.
		 */
		prio = tp->prio + 1;
		tp = tcf_chain_dereference(chain->filter_chain, chain);

		for (; tp; tp = tcf_chain_dereference(tp->next, chain))
			if (!tp->deleting && tp->prio >= prio)
				break;
	} else {
		tp = tcf_chain_dereference(tp->next, chain);
	}

	if (tp)
		tcf_proto_get(tp);

	mutex_unlock(&chain->filter_chain_lock);

	return tp;
}