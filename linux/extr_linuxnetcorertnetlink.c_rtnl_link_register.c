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
struct rtnl_link_ops {scalar_t__ maxtype; scalar_t__ slave_maxtype; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ RTNL_MAX_TYPE ; 
 scalar_t__ RTNL_SLAVE_MAX_TYPE ; 
 scalar_t__ WARN_ON (int) ; 
 int __rtnl_link_register (struct rtnl_link_ops*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

int rtnl_link_register(struct rtnl_link_ops *ops)
{
	int err;

	/* Sanity-check max sizes to avoid stack buffer overflow. */
	if (WARN_ON(ops->maxtype > RTNL_MAX_TYPE ||
		    ops->slave_maxtype > RTNL_SLAVE_MAX_TYPE))
		return -EINVAL;

	rtnl_lock();
	err = __rtnl_link_register(ops);
	rtnl_unlock();
	return err;
}