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
struct net_device {int flags; int /*<<< orphan*/  dn_ptr; } ;
struct dn_ifaddr {int /*<<< orphan*/  ifa_scope; struct dn_dev* ifa_dev; } ;
struct dn_dev {int dummy; } ;

/* Variables and functions */
 int IFF_LOOPBACK ; 
 int /*<<< orphan*/  RT_SCOPE_HOST ; 
 struct dn_dev* dn_dev_create (struct net_device*,int*) ; 
 int /*<<< orphan*/  dn_dev_free_ifa (struct dn_ifaddr*) ; 
 int dn_dev_insert_ifa (struct dn_dev*,struct dn_ifaddr*) ; 
 struct dn_dev* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dn_dev_set_ifa(struct net_device *dev, struct dn_ifaddr *ifa)
{
	struct dn_dev *dn_db = rtnl_dereference(dev->dn_ptr);
	int rv;

	if (dn_db == NULL) {
		int err;
		dn_db = dn_dev_create(dev, &err);
		if (dn_db == NULL)
			return err;
	}

	ifa->ifa_dev = dn_db;

	if (dev->flags & IFF_LOOPBACK)
		ifa->ifa_scope = RT_SCOPE_HOST;

	rv = dn_dev_insert_ifa(dn_db, ifa);
	if (rv)
		dn_dev_free_ifa(ifa);
	return rv;
}