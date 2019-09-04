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
struct dn_ifaddr {int dummy; } ;
struct dn_dev {int /*<<< orphan*/  ifa_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  dn_dev_del_ifa (struct dn_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_dev_delete (struct net_device*) ; 
 int /*<<< orphan*/  dn_dev_free_ifa (struct dn_ifaddr*) ; 
 void* rtnl_dereference (int /*<<< orphan*/ ) ; 

void dn_dev_down(struct net_device *dev)
{
	struct dn_dev *dn_db = rtnl_dereference(dev->dn_ptr);
	struct dn_ifaddr *ifa;

	if (dn_db == NULL)
		return;

	while ((ifa = rtnl_dereference(dn_db->ifa_list)) != NULL) {
		dn_dev_del_ifa(dn_db, &dn_db->ifa_list, 0);
		dn_dev_free_ifa(ifa);
	}

	dn_dev_delete(dev);
}