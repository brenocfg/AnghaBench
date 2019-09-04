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
struct dsa_switch {TYPE_1__* ops; } ;
struct dsa_notifier_fdb_info {int /*<<< orphan*/  vid; int /*<<< orphan*/  addr; int /*<<< orphan*/  port; int /*<<< orphan*/  sw_index; } ;
struct TYPE_2__ {int (* port_fdb_add ) (struct dsa_switch*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int dsa_towards_port (struct dsa_switch*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct dsa_switch*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsa_switch_fdb_add(struct dsa_switch *ds,
			      struct dsa_notifier_fdb_info *info)
{
	int port = dsa_towards_port(ds, info->sw_index, info->port);

	if (!ds->ops->port_fdb_add)
		return -EOPNOTSUPP;

	return ds->ops->port_fdb_add(ds, port, info->addr, info->vid);
}