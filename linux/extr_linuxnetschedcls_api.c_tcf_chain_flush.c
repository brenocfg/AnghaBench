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
struct tcf_proto {int /*<<< orphan*/  next; } ;
struct tcf_chain {int /*<<< orphan*/  filter_chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tcf_proto* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_chain0_head_change (struct tcf_chain*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_chain_put (struct tcf_chain*) ; 
 int /*<<< orphan*/  tcf_proto_destroy (struct tcf_proto*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tcf_chain_flush(struct tcf_chain *chain)
{
	struct tcf_proto *tp = rtnl_dereference(chain->filter_chain);

	tcf_chain0_head_change(chain, NULL);
	while (tp) {
		RCU_INIT_POINTER(chain->filter_chain, tp->next);
		tcf_proto_destroy(tp, NULL);
		tp = rtnl_dereference(chain->filter_chain);
		tcf_chain_put(chain);
	}
}