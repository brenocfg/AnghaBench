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
struct vlan_dev_priv {int /*<<< orphan*/ * vlan_pcpu_stats; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ *) ; 
 struct vlan_dev_priv* vlan_dev_priv (struct net_device*) ; 

__attribute__((used)) static void vlan_dev_free(struct net_device *dev)
{
	struct vlan_dev_priv *vlan = vlan_dev_priv(dev);

	free_percpu(vlan->vlan_pcpu_stats);
	vlan->vlan_pcpu_stats = NULL;
}