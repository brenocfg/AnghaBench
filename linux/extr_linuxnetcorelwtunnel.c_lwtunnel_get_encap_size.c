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
struct lwtunnel_state {size_t type; } ;
struct lwtunnel_encap_ops {int /*<<< orphan*/  (* get_encap_size ) (struct lwtunnel_state*) ;} ;

/* Variables and functions */
 size_t LWTUNNEL_ENCAP_MAX ; 
 size_t LWTUNNEL_ENCAP_NONE ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/ * lwtun_encaps ; 
 int nla_total_size (int /*<<< orphan*/ ) ; 
 struct lwtunnel_encap_ops* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (struct lwtunnel_state*) ; 

int lwtunnel_get_encap_size(struct lwtunnel_state *lwtstate)
{
	const struct lwtunnel_encap_ops *ops;
	int ret = 0;

	if (!lwtstate)
		return 0;

	if (lwtstate->type == LWTUNNEL_ENCAP_NONE ||
	    lwtstate->type > LWTUNNEL_ENCAP_MAX)
		return 0;

	rcu_read_lock();
	ops = rcu_dereference(lwtun_encaps[lwtstate->type]);
	if (likely(ops && ops->get_encap_size))
		ret = nla_total_size(ops->get_encap_size(lwtstate));
	rcu_read_unlock();

	return ret;
}