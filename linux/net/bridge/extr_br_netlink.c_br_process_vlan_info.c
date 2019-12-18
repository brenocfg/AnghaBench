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
struct netlink_ext_ack {int dummy; } ;
struct net_bridge_port {int dummy; } ;
struct net_bridge {int dummy; } ;
struct bridge_vlan_info {scalar_t__ vid; int flags; } ;

/* Variables and functions */
 int BRIDGE_VLAN_INFO_PVID ; 
 int BRIDGE_VLAN_INFO_RANGE_BEGIN ; 
 int BRIDGE_VLAN_INFO_RANGE_END ; 
 int EINVAL ; 
 scalar_t__ VLAN_VID_MASK ; 
 int br_vlan_info (struct net_bridge*,struct net_bridge_port*,int,struct bridge_vlan_info*,int*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  memcpy (struct bridge_vlan_info*,struct bridge_vlan_info*,int) ; 

__attribute__((used)) static int br_process_vlan_info(struct net_bridge *br,
				struct net_bridge_port *p, int cmd,
				struct bridge_vlan_info *vinfo_curr,
				struct bridge_vlan_info **vinfo_last,
				bool *changed,
				struct netlink_ext_ack *extack)
{
	if (!vinfo_curr->vid || vinfo_curr->vid >= VLAN_VID_MASK)
		return -EINVAL;

	if (vinfo_curr->flags & BRIDGE_VLAN_INFO_RANGE_BEGIN) {
		/* check if we are already processing a range */
		if (*vinfo_last)
			return -EINVAL;
		*vinfo_last = vinfo_curr;
		/* don't allow range of pvids */
		if ((*vinfo_last)->flags & BRIDGE_VLAN_INFO_PVID)
			return -EINVAL;
		return 0;
	}

	if (*vinfo_last) {
		struct bridge_vlan_info tmp_vinfo;
		int v, err;

		if (!(vinfo_curr->flags & BRIDGE_VLAN_INFO_RANGE_END))
			return -EINVAL;

		if (vinfo_curr->vid <= (*vinfo_last)->vid)
			return -EINVAL;

		memcpy(&tmp_vinfo, *vinfo_last,
		       sizeof(struct bridge_vlan_info));
		for (v = (*vinfo_last)->vid; v <= vinfo_curr->vid; v++) {
			tmp_vinfo.vid = v;
			err = br_vlan_info(br, p, cmd, &tmp_vinfo, changed,
					   extack);
			if (err)
				break;
		}
		*vinfo_last = NULL;

		return err;
	}

	return br_vlan_info(br, p, cmd, vinfo_curr, changed, extack);
}