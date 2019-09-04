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
struct TYPE_6__ {int id_len; int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_3__ ppid; } ;
struct switchdev_attr {int id; TYPE_2__ u; } ;
struct netdevsim {TYPE_1__* sdev; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  switch_id; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  SWITCHDEV_ATTR_ID_PORT_PARENT_ID 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct netdevsim* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
nsim_port_attr_get(struct net_device *dev, struct switchdev_attr *attr)
{
	struct netdevsim *ns = netdev_priv(dev);

	switch (attr->id) {
	case SWITCHDEV_ATTR_ID_PORT_PARENT_ID:
		attr->u.ppid.id_len = sizeof(ns->sdev->switch_id);
		memcpy(&attr->u.ppid.id, &ns->sdev->switch_id,
		       attr->u.ppid.id_len);
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}