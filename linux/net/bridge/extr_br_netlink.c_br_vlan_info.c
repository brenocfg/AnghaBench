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
struct net_bridge_port {struct net_bridge* br; } ;
struct net_bridge {int dummy; } ;
struct bridge_vlan_info {int flags; int /*<<< orphan*/  vid; } ;

/* Variables and functions */
 int BRIDGE_VLAN_INFO_BRENTRY ; 
 int BRIDGE_VLAN_INFO_MASTER ; 
#define  RTM_DELLINK 129 
#define  RTM_SETLINK 128 
 int br_vlan_add (struct net_bridge*,int /*<<< orphan*/ ,int,int*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  br_vlan_delete (struct net_bridge*,int /*<<< orphan*/ ) ; 
 int nbp_vlan_add (struct net_bridge_port*,int /*<<< orphan*/ ,int,int*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  nbp_vlan_delete (struct net_bridge_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int br_vlan_info(struct net_bridge *br, struct net_bridge_port *p,
			int cmd, struct bridge_vlan_info *vinfo, bool *changed,
			struct netlink_ext_ack *extack)
{
	bool curr_change;
	int err = 0;

	switch (cmd) {
	case RTM_SETLINK:
		if (p) {
			/* if the MASTER flag is set this will act on the global
			 * per-VLAN entry as well
			 */
			err = nbp_vlan_add(p, vinfo->vid, vinfo->flags,
					   &curr_change, extack);
		} else {
			vinfo->flags |= BRIDGE_VLAN_INFO_BRENTRY;
			err = br_vlan_add(br, vinfo->vid, vinfo->flags,
					  &curr_change, extack);
		}
		if (curr_change)
			*changed = true;
		break;

	case RTM_DELLINK:
		if (p) {
			if (!nbp_vlan_delete(p, vinfo->vid))
				*changed = true;

			if ((vinfo->flags & BRIDGE_VLAN_INFO_MASTER) &&
			    !br_vlan_delete(p->br, vinfo->vid))
				*changed = true;
		} else if (!br_vlan_delete(br, vinfo->vid)) {
			*changed = true;
		}
		break;
	}

	return err;
}