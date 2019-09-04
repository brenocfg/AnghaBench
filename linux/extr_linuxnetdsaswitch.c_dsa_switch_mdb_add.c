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
struct switchdev_trans {int dummy; } ;
struct switchdev_obj_port_mdb {int dummy; } ;
struct dsa_switch {int num_ports; scalar_t__ index; int /*<<< orphan*/  bitmap; } ;
struct dsa_notifier_mdb_info {scalar_t__ sw_index; int port; struct switchdev_trans* trans; struct switchdev_obj_port_mdb* mdb; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int) ; 
 scalar_t__ dsa_is_dsa_port (struct dsa_switch*,int) ; 
 int /*<<< orphan*/  dsa_switch_mdb_add_bitmap (struct dsa_switch*,struct switchdev_obj_port_mdb const*,int /*<<< orphan*/ ) ; 
 int dsa_switch_mdb_prepare_bitmap (struct dsa_switch*,struct switchdev_obj_port_mdb const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ switchdev_trans_ph_prepare (struct switchdev_trans*) ; 

__attribute__((used)) static int dsa_switch_mdb_add(struct dsa_switch *ds,
			      struct dsa_notifier_mdb_info *info)
{
	const struct switchdev_obj_port_mdb *mdb = info->mdb;
	struct switchdev_trans *trans = info->trans;
	int port;

	/* Build a mask of Multicast group members */
	bitmap_zero(ds->bitmap, ds->num_ports);
	if (ds->index == info->sw_index)
		set_bit(info->port, ds->bitmap);
	for (port = 0; port < ds->num_ports; port++)
		if (dsa_is_dsa_port(ds, port))
			set_bit(port, ds->bitmap);

	if (switchdev_trans_ph_prepare(trans))
		return dsa_switch_mdb_prepare_bitmap(ds, mdb, ds->bitmap);

	dsa_switch_mdb_add_bitmap(ds, mdb, ds->bitmap);

	return 0;
}