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
typedef  int u16 ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct net_bridge_vlan_group {int /*<<< orphan*/  num_vlans; int /*<<< orphan*/  vlan_hash; } ;
struct net_bridge_vlan {int /*<<< orphan*/  vid; struct net_bridge_vlan* brvlan; int /*<<< orphan*/  vnode; int /*<<< orphan*/  stats; struct net_bridge_port* port; struct net_bridge* br; } ;
struct net_bridge_port {struct net_device* dev; struct net_bridge* br; } ;
struct net_bridge {struct net_device* dev; } ;

/* Variables and functions */
 int BRIDGE_VLAN_INFO_BRENTRY ; 
 int BRIDGE_VLAN_INFO_MASTER ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  __vlan_add_flags (struct net_bridge_vlan*,int) ; 
 int /*<<< orphan*/  __vlan_add_list (struct net_bridge_vlan*) ; 
 int __vlan_vid_add (struct net_device*,struct net_bridge*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __vlan_vid_del (struct net_device*,struct net_bridge*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_err (struct net_bridge*,char*) ; 
 int /*<<< orphan*/  br_fdb_find_delete_local (struct net_bridge*,struct net_bridge_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int br_fdb_insert (struct net_bridge*,struct net_bridge_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int br_switchdev_port_vlan_add (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  br_switchdev_port_vlan_del (struct net_device*,int /*<<< orphan*/ ) ; 
 int br_vlan_add (struct net_bridge*,int /*<<< orphan*/ ,int,int*) ; 
 struct net_bridge_vlan* br_vlan_get_master (struct net_bridge*,int /*<<< orphan*/ ) ; 
 struct net_bridge_vlan_group* br_vlan_group (struct net_bridge*) ; 
 scalar_t__ br_vlan_is_master (struct net_bridge_vlan*) ; 
 int /*<<< orphan*/  br_vlan_put_master (struct net_bridge_vlan*) ; 
 int /*<<< orphan*/  br_vlan_rht_params ; 
 scalar_t__ br_vlan_should_use (struct net_bridge_vlan*) ; 
 struct net_bridge_vlan_group* nbp_vlan_group (struct net_bridge_port*) ; 
 int rhashtable_lookup_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __vlan_add(struct net_bridge_vlan *v, u16 flags)
{
	struct net_bridge_vlan *masterv = NULL;
	struct net_bridge_port *p = NULL;
	struct net_bridge_vlan_group *vg;
	struct net_device *dev;
	struct net_bridge *br;
	int err;

	if (br_vlan_is_master(v)) {
		br = v->br;
		dev = br->dev;
		vg = br_vlan_group(br);
	} else {
		p = v->port;
		br = p->br;
		dev = p->dev;
		vg = nbp_vlan_group(p);
	}

	if (p) {
		/* Add VLAN to the device filter if it is supported.
		 * This ensures tagged traffic enters the bridge when
		 * promiscuous mode is disabled by br_manage_promisc().
		 */
		err = __vlan_vid_add(dev, br, v->vid, flags);
		if (err)
			goto out;

		/* need to work on the master vlan too */
		if (flags & BRIDGE_VLAN_INFO_MASTER) {
			bool changed;

			err = br_vlan_add(br, v->vid,
					  flags | BRIDGE_VLAN_INFO_BRENTRY,
					  &changed);
			if (err)
				goto out_filt;
		}

		masterv = br_vlan_get_master(br, v->vid);
		if (!masterv)
			goto out_filt;
		v->brvlan = masterv;
		v->stats = masterv->stats;
	} else {
		err = br_switchdev_port_vlan_add(dev, v->vid, flags);
		if (err && err != -EOPNOTSUPP)
			goto out;
	}

	/* Add the dev mac and count the vlan only if it's usable */
	if (br_vlan_should_use(v)) {
		err = br_fdb_insert(br, p, dev->dev_addr, v->vid);
		if (err) {
			br_err(br, "failed insert local address into bridge forwarding table\n");
			goto out_filt;
		}
		vg->num_vlans++;
	}

	err = rhashtable_lookup_insert_fast(&vg->vlan_hash, &v->vnode,
					    br_vlan_rht_params);
	if (err)
		goto out_fdb_insert;

	__vlan_add_list(v);
	__vlan_add_flags(v, flags);
out:
	return err;

out_fdb_insert:
	if (br_vlan_should_use(v)) {
		br_fdb_find_delete_local(br, p, dev->dev_addr, v->vid);
		vg->num_vlans--;
	}

out_filt:
	if (p) {
		__vlan_vid_del(dev, br, v->vid);
		if (masterv) {
			br_vlan_put_master(masterv);
			v->brvlan = NULL;
		}
	} else {
		br_switchdev_port_vlan_del(dev, v->vid);
	}

	goto out;
}