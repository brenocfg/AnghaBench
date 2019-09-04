#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_bridge_port {int /*<<< orphan*/  sysfs_name; int /*<<< orphan*/  kobj; TYPE_3__* dev; struct net_bridge* br; } ;
struct net_bridge {int /*<<< orphan*/ * ifobj; TYPE_2__* dev; } ;
struct brport_attribute {int /*<<< orphan*/  attr; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  SYSFS_BRIDGE_PORT_LINK ; 
 struct brport_attribute** brport_attrs ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sysfs_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sysfs_create_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int br_sysfs_addif(struct net_bridge_port *p)
{
	struct net_bridge *br = p->br;
	const struct brport_attribute **a;
	int err;

	err = sysfs_create_link(&p->kobj, &br->dev->dev.kobj,
				SYSFS_BRIDGE_PORT_LINK);
	if (err)
		return err;

	for (a = brport_attrs; *a; ++a) {
		err = sysfs_create_file(&p->kobj, &((*a)->attr));
		if (err)
			return err;
	}

	strlcpy(p->sysfs_name, p->dev->name, IFNAMSIZ);
	return sysfs_create_link(br->ifobj, &p->kobj, p->sysfs_name);
}