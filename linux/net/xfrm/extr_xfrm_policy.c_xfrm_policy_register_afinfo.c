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
struct dst_ops {scalar_t__ confirm_neigh; int /*<<< orphan*/ * neigh_lookup; int /*<<< orphan*/ * link_failure; int /*<<< orphan*/ * negative_advice; int /*<<< orphan*/ * mtu; int /*<<< orphan*/ * default_advmss; int /*<<< orphan*/ * check; int /*<<< orphan*/ * kmem_cachep; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int EAFNOSUPPORT ; 
 int EEXIST ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ *,struct xfrm_policy_afinfo const*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__ xfrm_confirm_neigh ; 
 int /*<<< orphan*/ * xfrm_default_advmss ; 
 int /*<<< orphan*/ * xfrm_dst_cache ; 
 int /*<<< orphan*/ * xfrm_dst_check ; 
 int /*<<< orphan*/ * xfrm_link_failure ; 
 int /*<<< orphan*/ * xfrm_mtu ; 
 int /*<<< orphan*/ * xfrm_negative_advice ; 
 int /*<<< orphan*/ * xfrm_neigh_lookup ; 
 int /*<<< orphan*/ ** xfrm_policy_afinfo ; 
 int /*<<< orphan*/  xfrm_policy_afinfo_lock ; 

int xfrm_policy_register_afinfo(const struct xfrm_policy_afinfo *afinfo, int family)
{
	int err = 0;

	if (WARN_ON(family >= ARRAY_SIZE(xfrm_policy_afinfo)))
		return -EAFNOSUPPORT;

	spin_lock(&xfrm_policy_afinfo_lock);
	if (unlikely(xfrm_policy_afinfo[family] != NULL))
		err = -EEXIST;
	else {
		struct dst_ops *dst_ops = afinfo->dst_ops;
		if (likely(dst_ops->kmem_cachep == NULL))
			dst_ops->kmem_cachep = xfrm_dst_cache;
		if (likely(dst_ops->check == NULL))
			dst_ops->check = xfrm_dst_check;
		if (likely(dst_ops->default_advmss == NULL))
			dst_ops->default_advmss = xfrm_default_advmss;
		if (likely(dst_ops->mtu == NULL))
			dst_ops->mtu = xfrm_mtu;
		if (likely(dst_ops->negative_advice == NULL))
			dst_ops->negative_advice = xfrm_negative_advice;
		if (likely(dst_ops->link_failure == NULL))
			dst_ops->link_failure = xfrm_link_failure;
		if (likely(dst_ops->neigh_lookup == NULL))
			dst_ops->neigh_lookup = xfrm_neigh_lookup;
		if (likely(!dst_ops->confirm_neigh))
			dst_ops->confirm_neigh = xfrm_confirm_neigh;
		rcu_assign_pointer(xfrm_policy_afinfo[family], afinfo);
	}
	spin_unlock(&xfrm_policy_afinfo_lock);

	return err;
}