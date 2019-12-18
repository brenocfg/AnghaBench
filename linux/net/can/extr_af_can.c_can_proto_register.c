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
struct can_proto {int protocol; int /*<<< orphan*/  prot; } ;

/* Variables and functions */
 int CAN_NPROTO ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,struct can_proto const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int proto_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * proto_tab ; 
 int /*<<< orphan*/  proto_tab_lock ; 
 int /*<<< orphan*/  proto_unregister (int /*<<< orphan*/ ) ; 
 scalar_t__ rcu_access_pointer (int /*<<< orphan*/ ) ; 

int can_proto_register(const struct can_proto *cp)
{
	int proto = cp->protocol;
	int err = 0;

	if (proto < 0 || proto >= CAN_NPROTO) {
		pr_err("can: protocol number %d out of range\n", proto);
		return -EINVAL;
	}

	err = proto_register(cp->prot, 0);
	if (err < 0)
		return err;

	mutex_lock(&proto_tab_lock);

	if (rcu_access_pointer(proto_tab[proto])) {
		pr_err("can: protocol %d already registered\n", proto);
		err = -EBUSY;
	} else {
		RCU_INIT_POINTER(proto_tab[proto], cp);
	}

	mutex_unlock(&proto_tab_lock);

	if (err < 0)
		proto_unregister(cp->prot);

	return err;
}