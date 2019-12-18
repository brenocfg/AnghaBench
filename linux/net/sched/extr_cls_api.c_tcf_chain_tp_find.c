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
struct tcf_proto {scalar_t__ prio; scalar_t__ protocol; struct tcf_proto* next; } ;
struct tcf_chain_info {struct tcf_proto* next; struct tcf_proto** pprev; } ;
struct tcf_chain {struct tcf_proto* filter_chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct tcf_proto* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct tcf_proto* tcf_chain_dereference (struct tcf_proto*,struct tcf_chain*) ; 
 int /*<<< orphan*/  tcf_proto_get (struct tcf_proto*) ; 

__attribute__((used)) static struct tcf_proto *tcf_chain_tp_find(struct tcf_chain *chain,
					   struct tcf_chain_info *chain_info,
					   u32 protocol, u32 prio,
					   bool prio_allocate)
{
	struct tcf_proto **pprev;
	struct tcf_proto *tp;

	/* Check the chain for existence of proto-tcf with this priority */
	for (pprev = &chain->filter_chain;
	     (tp = tcf_chain_dereference(*pprev, chain));
	     pprev = &tp->next) {
		if (tp->prio >= prio) {
			if (tp->prio == prio) {
				if (prio_allocate ||
				    (tp->protocol != protocol && protocol))
					return ERR_PTR(-EINVAL);
			} else {
				tp = NULL;
			}
			break;
		}
	}
	chain_info->pprev = pprev;
	if (tp) {
		chain_info->next = tp->next;
		tcf_proto_get(tp);
	} else {
		chain_info->next = NULL;
	}
	return tp;
}