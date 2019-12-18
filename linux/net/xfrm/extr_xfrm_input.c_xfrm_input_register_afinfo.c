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
 size_t ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int EAFNOSUPPORT ; 
 int EEXIST ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ *,struct xfrm_input_afinfo const*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** xfrm_input_afinfo ; 
 int /*<<< orphan*/  xfrm_input_afinfo_lock ; 

int xfrm_input_register_afinfo(const struct xfrm_input_afinfo *afinfo)
{
	int err = 0;

	if (WARN_ON(afinfo->family >= ARRAY_SIZE(xfrm_input_afinfo)))
		return -EAFNOSUPPORT;

	spin_lock_bh(&xfrm_input_afinfo_lock);
	if (unlikely(xfrm_input_afinfo[afinfo->family] != NULL))
		err = -EEXIST;
	else
		rcu_assign_pointer(xfrm_input_afinfo[afinfo->family], afinfo);
	spin_unlock_bh(&xfrm_input_afinfo_lock);
	return err;
}