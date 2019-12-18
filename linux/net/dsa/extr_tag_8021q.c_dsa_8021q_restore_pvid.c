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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct dsa_switch {TYPE_1__* ports; int /*<<< orphan*/  dev; } ;
struct bridge_vlan_info {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {struct net_device* slave; } ;

/* Variables and functions */
 int br_vlan_get_info (struct net_device*,int /*<<< orphan*/ ,struct bridge_vlan_info*) ; 
 int br_vlan_get_pvid (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dsa_is_user_port (struct dsa_switch*,int) ; 
 int dsa_port_vid_add (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsa_8021q_restore_pvid(struct dsa_switch *ds, int port)
{
	struct bridge_vlan_info vinfo;
	struct net_device *slave;
	u16 pvid;
	int err;

	if (!dsa_is_user_port(ds, port))
		return 0;

	slave = ds->ports[port].slave;

	err = br_vlan_get_pvid(slave, &pvid);
	if (err < 0)
		/* There is no pvid on the bridge for this port, which is
		 * perfectly valid. Nothing to restore, bye-bye!
		 */
		return 0;

	err = br_vlan_get_info(slave, pvid, &vinfo);
	if (err < 0) {
		dev_err(ds->dev, "Couldn't determine PVID attributes\n");
		return err;
	}

	return dsa_port_vid_add(&ds->ports[port], pvid, vinfo.flags);
}