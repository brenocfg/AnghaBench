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
struct net_proto_family {size_t family; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOBUFS ; 
 size_t NPROTO ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * net_families ; 
 int /*<<< orphan*/  net_family_lock ; 
 int /*<<< orphan*/  pr_crit (char*,size_t,size_t) ; 
 int /*<<< orphan*/  pr_info (char*,size_t) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct net_proto_family const*) ; 
 scalar_t__ rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int sock_register(const struct net_proto_family *ops)
{
	int err;

	if (ops->family >= NPROTO) {
		pr_crit("protocol %d >= NPROTO(%d)\n", ops->family, NPROTO);
		return -ENOBUFS;
	}

	spin_lock(&net_family_lock);
	if (rcu_dereference_protected(net_families[ops->family],
				      lockdep_is_held(&net_family_lock)))
		err = -EEXIST;
	else {
		rcu_assign_pointer(net_families[ops->family], ops);
		err = 0;
	}
	spin_unlock(&net_family_lock);

	pr_info("NET: Registered protocol family %d\n", ops->family);
	return err;
}