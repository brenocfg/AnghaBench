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
struct dsa_switch {int num_ports; TYPE_1__* ops; } ;
struct dsa_notifier_mdb_info {int /*<<< orphan*/  mdb; int /*<<< orphan*/  trans; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* port_mdb_add ) (struct dsa_switch*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ dsa_switch_mdb_match (struct dsa_switch*,int,struct dsa_notifier_mdb_info*) ; 
 int dsa_switch_mdb_prepare (struct dsa_switch*,struct dsa_notifier_mdb_info*) ; 
 int /*<<< orphan*/  stub1 (struct dsa_switch*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ switchdev_trans_ph_prepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsa_switch_mdb_add(struct dsa_switch *ds,
			      struct dsa_notifier_mdb_info *info)
{
	int port;

	if (switchdev_trans_ph_prepare(info->trans))
		return dsa_switch_mdb_prepare(ds, info);

	if (!ds->ops->port_mdb_add)
		return 0;

	for (port = 0; port < ds->num_ports; port++)
		if (dsa_switch_mdb_match(ds, port, info))
			ds->ops->port_mdb_add(ds, port, info->mdb);

	return 0;
}