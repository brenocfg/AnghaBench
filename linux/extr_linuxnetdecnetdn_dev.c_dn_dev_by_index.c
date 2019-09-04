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
struct net_device {int /*<<< orphan*/  dn_ptr; } ;
struct dn_dev {int dummy; } ;

/* Variables and functions */
 struct net_device* __dev_get_by_index (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_net ; 
 struct dn_dev* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dn_dev *dn_dev_by_index(int ifindex)
{
	struct net_device *dev;
	struct dn_dev *dn_dev = NULL;

	dev = __dev_get_by_index(&init_net, ifindex);
	if (dev)
		dn_dev = rtnl_dereference(dev->dn_ptr);

	return dn_dev;
}