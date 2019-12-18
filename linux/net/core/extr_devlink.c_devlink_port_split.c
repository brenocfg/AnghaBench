#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct netlink_ext_ack {int dummy; } ;
struct devlink {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* port_split ) (struct devlink*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct devlink*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 

__attribute__((used)) static int devlink_port_split(struct devlink *devlink, u32 port_index,
			      u32 count, struct netlink_ext_ack *extack)

{
	if (devlink->ops->port_split)
		return devlink->ops->port_split(devlink, port_index, count,
						extack);
	return -EOPNOTSUPP;
}