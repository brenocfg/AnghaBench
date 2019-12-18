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
typedef  int /*<<< orphan*/  u16 ;
struct dsa_switch {struct dsa_port* ports; } ;
struct dsa_port {struct dsa_port* cpu_dp; int /*<<< orphan*/  slave; } ;
struct bridge_vlan_info {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_VLAN_INFO_PVID ; 
 int br_vlan_get_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bridge_vlan_info*) ; 
 int /*<<< orphan*/  dsa_is_user_port (struct dsa_switch*,int) ; 
 int dsa_port_vid_add (struct dsa_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dsa_port_vid_del (struct dsa_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsa_8021q_vid_apply(struct dsa_switch *ds, int port, u16 vid,
			       u16 flags, bool enabled)
{
	struct dsa_port *dp = &ds->ports[port];
	struct bridge_vlan_info vinfo;
	int err;

	if (enabled)
		return dsa_port_vid_add(dp, vid, flags);

	err = dsa_port_vid_del(dp, vid);
	if (err < 0)
		return err;

	/* Nothing to restore from the bridge for a non-user port.
	 * The CPU port VLANs are restored implicitly with the user ports,
	 * similar to how the bridge does in dsa_slave_vlan_add and
	 * dsa_slave_vlan_del.
	 */
	if (!dsa_is_user_port(ds, port))
		return 0;

	err = br_vlan_get_info(dp->slave, vid, &vinfo);
	/* Couldn't determine bridge attributes for this vid,
	 * it means the bridge had not configured it.
	 */
	if (err < 0)
		return 0;

	/* Restore the VID from the bridge */
	err = dsa_port_vid_add(dp, vid, vinfo.flags);
	if (err < 0)
		return err;

	vinfo.flags &= ~BRIDGE_VLAN_INFO_PVID;

	return dsa_port_vid_add(dp->cpu_dp, vid, vinfo.flags);
}