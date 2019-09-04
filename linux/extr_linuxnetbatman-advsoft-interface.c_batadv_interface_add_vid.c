#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct batadv_softif_vlan {int /*<<< orphan*/  kobj; } ;
struct batadv_priv {TYPE_1__* soft_iface; } ;
typedef  scalar_t__ __be16 ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_NO_MARK ; 
 int /*<<< orphan*/  BATADV_NULL_IFINDEX ; 
 unsigned short BATADV_VLAN_HAS_TAG ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int batadv_softif_create_vlan (struct batadv_priv*,unsigned short) ; 
 struct batadv_softif_vlan* batadv_softif_vlan_get (struct batadv_priv*,unsigned short) ; 
 int /*<<< orphan*/  batadv_softif_vlan_put (struct batadv_softif_vlan*) ; 
 int batadv_sysfs_add_vlan (TYPE_1__*,struct batadv_softif_vlan*) ; 
 int /*<<< orphan*/  batadv_tt_local_add (TYPE_1__*,int /*<<< orphan*/ ,unsigned short,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct batadv_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int batadv_interface_add_vid(struct net_device *dev, __be16 proto,
				    unsigned short vid)
{
	struct batadv_priv *bat_priv = netdev_priv(dev);
	struct batadv_softif_vlan *vlan;
	int ret;

	/* only 802.1Q vlans are supported.
	 * batman-adv does not know how to handle other types
	 */
	if (proto != htons(ETH_P_8021Q))
		return -EINVAL;

	vid |= BATADV_VLAN_HAS_TAG;

	/* if a new vlan is getting created and it already exists, it means that
	 * it was not deleted yet. batadv_softif_vlan_get() increases the
	 * refcount in order to revive the object.
	 *
	 * if it does not exist then create it.
	 */
	vlan = batadv_softif_vlan_get(bat_priv, vid);
	if (!vlan)
		return batadv_softif_create_vlan(bat_priv, vid);

	/* recreate the sysfs object if it was already destroyed (and it should
	 * be since we received a kill_vid() for this vlan
	 */
	if (!vlan->kobj) {
		ret = batadv_sysfs_add_vlan(bat_priv->soft_iface, vlan);
		if (ret) {
			batadv_softif_vlan_put(vlan);
			return ret;
		}
	}

	/* add a new TT local entry. This one will be marked with the NOPURGE
	 * flag. This must be added again, even if the vlan object already
	 * exists, because the entry was deleted by kill_vid()
	 */
	batadv_tt_local_add(bat_priv->soft_iface,
			    bat_priv->soft_iface->dev_addr, vid,
			    BATADV_NULL_IFINDEX, BATADV_NO_MARK);

	return 0;
}