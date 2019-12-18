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
struct xfrm_policy_afinfo {struct dst_ops* dst_ops; } ;
struct dst_ops {int /*<<< orphan*/ * link_failure; int /*<<< orphan*/ * negative_advice; int /*<<< orphan*/ * check; int /*<<< orphan*/ * kmem_cachep; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct xfrm_policy_afinfo const**) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (struct xfrm_policy_afinfo const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 struct xfrm_policy_afinfo const** xfrm_policy_afinfo ; 

void xfrm_policy_unregister_afinfo(const struct xfrm_policy_afinfo *afinfo)
{
	struct dst_ops *dst_ops = afinfo->dst_ops;
	int i;

	for (i = 0; i < ARRAY_SIZE(xfrm_policy_afinfo); i++) {
		if (xfrm_policy_afinfo[i] != afinfo)
			continue;
		RCU_INIT_POINTER(xfrm_policy_afinfo[i], NULL);
		break;
	}

	synchronize_rcu();

	dst_ops->kmem_cachep = NULL;
	dst_ops->check = NULL;
	dst_ops->negative_advice = NULL;
	dst_ops->link_failure = NULL;
}