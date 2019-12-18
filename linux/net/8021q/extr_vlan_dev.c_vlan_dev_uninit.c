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
struct vlan_priority_tci_mapping {struct vlan_priority_tci_mapping* next; } ;
struct vlan_dev_priv {struct vlan_priority_tci_mapping** egress_priority_map; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct vlan_priority_tci_mapping**) ; 
 int /*<<< orphan*/  kfree (struct vlan_priority_tci_mapping*) ; 
 struct vlan_dev_priv* vlan_dev_priv (struct net_device*) ; 

__attribute__((used)) static void vlan_dev_uninit(struct net_device *dev)
{
	struct vlan_priority_tci_mapping *pm;
	struct vlan_dev_priv *vlan = vlan_dev_priv(dev);
	int i;

	for (i = 0; i < ARRAY_SIZE(vlan->egress_priority_map); i++) {
		while ((pm = vlan->egress_priority_map[i]) != NULL) {
			vlan->egress_priority_map[i] = pm->next;
			kfree(pm);
		}
	}
}