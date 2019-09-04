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
typedef  int /*<<< orphan*/  vlan_id ;
struct vlan_dev_priv {int /*<<< orphan*/  real_dev; int /*<<< orphan*/  vlan_proto; int /*<<< orphan*/  vlan_id; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  GVRP_ATTR_VID ; 
 int /*<<< orphan*/  garp_request_leave (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct vlan_dev_priv* vlan_dev_priv (struct net_device const*) ; 
 int /*<<< orphan*/  vlan_gvrp_app ; 

void vlan_gvrp_request_leave(const struct net_device *dev)
{
	const struct vlan_dev_priv *vlan = vlan_dev_priv(dev);
	__be16 vlan_id = htons(vlan->vlan_id);

	if (vlan->vlan_proto != htons(ETH_P_8021Q))
		return;
	garp_request_leave(vlan->real_dev, &vlan_gvrp_app,
			   &vlan_id, sizeof(vlan_id), GVRP_ATTR_VID);
}