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
struct xfrm_state_afinfo {int family; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int NPROTO ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 struct xfrm_state_afinfo* rcu_access_pointer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/ ** xfrm_state_afinfo ; 
 int /*<<< orphan*/  xfrm_state_afinfo_lock ; 

int xfrm_state_unregister_afinfo(struct xfrm_state_afinfo *afinfo)
{
	int err = 0, family = afinfo->family;

	if (WARN_ON(family >= NPROTO))
		return -EAFNOSUPPORT;

	spin_lock_bh(&xfrm_state_afinfo_lock);
	if (likely(xfrm_state_afinfo[afinfo->family] != NULL)) {
		if (rcu_access_pointer(xfrm_state_afinfo[family]) != afinfo)
			err = -EINVAL;
		else
			RCU_INIT_POINTER(xfrm_state_afinfo[afinfo->family], NULL);
	}
	spin_unlock_bh(&xfrm_state_afinfo_lock);
	synchronize_rcu();
	return err;
}