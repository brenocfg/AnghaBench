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
struct net_device {int /*<<< orphan*/  mpls_ptr; } ;
struct mpls_dev {int dummy; } ;

/* Variables and functions */
 struct mpls_dev* rcu_dereference_rtnl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct mpls_dev *mpls_dev_get(const struct net_device *dev)
{
	return rcu_dereference_rtnl(dev->mpls_ptr);
}