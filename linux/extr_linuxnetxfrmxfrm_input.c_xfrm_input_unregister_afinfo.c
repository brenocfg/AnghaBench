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
struct xfrm_input_afinfo {size_t family; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (struct xfrm_input_afinfo const*,int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 scalar_t__ unlikely (int) ; 
 struct xfrm_input_afinfo const** xfrm_input_afinfo ; 
 int /*<<< orphan*/  xfrm_input_afinfo_lock ; 

int xfrm_input_unregister_afinfo(const struct xfrm_input_afinfo *afinfo)
{
	int err = 0;

	spin_lock_bh(&xfrm_input_afinfo_lock);
	if (likely(xfrm_input_afinfo[afinfo->family] != NULL)) {
		if (unlikely(xfrm_input_afinfo[afinfo->family] != afinfo))
			err = -EINVAL;
		else
			RCU_INIT_POINTER(xfrm_input_afinfo[afinfo->family], NULL);
	}
	spin_unlock_bh(&xfrm_input_afinfo_lock);
	synchronize_rcu();
	return err;
}