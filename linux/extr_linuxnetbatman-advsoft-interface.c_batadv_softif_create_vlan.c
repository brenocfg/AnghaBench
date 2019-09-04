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
struct batadv_softif_vlan {unsigned short vid; int /*<<< orphan*/  list; int /*<<< orphan*/  refcount; int /*<<< orphan*/  ap_isolation; struct batadv_priv* bat_priv; } ;
struct batadv_priv {TYPE_1__* soft_iface; int /*<<< orphan*/  softif_vlan_list_lock; int /*<<< orphan*/  softif_vlan_list; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_NO_MARK ; 
 int /*<<< orphan*/  BATADV_NULL_IFINDEX ; 
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct batadv_softif_vlan* batadv_softif_vlan_get (struct batadv_priv*,unsigned short) ; 
 int /*<<< orphan*/  batadv_softif_vlan_put (struct batadv_softif_vlan*) ; 
 int batadv_sysfs_add_vlan (TYPE_1__*,struct batadv_softif_vlan*) ; 
 int /*<<< orphan*/  batadv_tt_local_add (TYPE_1__*,int /*<<< orphan*/ ,unsigned short,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct batadv_softif_vlan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int batadv_softif_create_vlan(struct batadv_priv *bat_priv, unsigned short vid)
{
	struct batadv_softif_vlan *vlan;
	int err;

	spin_lock_bh(&bat_priv->softif_vlan_list_lock);

	vlan = batadv_softif_vlan_get(bat_priv, vid);
	if (vlan) {
		batadv_softif_vlan_put(vlan);
		spin_unlock_bh(&bat_priv->softif_vlan_list_lock);
		return -EEXIST;
	}

	vlan = kzalloc(sizeof(*vlan), GFP_ATOMIC);
	if (!vlan) {
		spin_unlock_bh(&bat_priv->softif_vlan_list_lock);
		return -ENOMEM;
	}

	vlan->bat_priv = bat_priv;
	vlan->vid = vid;
	kref_init(&vlan->refcount);

	atomic_set(&vlan->ap_isolation, 0);

	kref_get(&vlan->refcount);
	hlist_add_head_rcu(&vlan->list, &bat_priv->softif_vlan_list);
	spin_unlock_bh(&bat_priv->softif_vlan_list_lock);

	/* batadv_sysfs_add_vlan cannot be in the spinlock section due to the
	 * sleeping behavior of the sysfs functions and the fs_reclaim lock
	 */
	err = batadv_sysfs_add_vlan(bat_priv->soft_iface, vlan);
	if (err) {
		/* ref for the function */
		batadv_softif_vlan_put(vlan);

		/* ref for the list */
		batadv_softif_vlan_put(vlan);
		return err;
	}

	/* add a new TT local entry. This one will be marked with the NOPURGE
	 * flag
	 */
	batadv_tt_local_add(bat_priv->soft_iface,
			    bat_priv->soft_iface->dev_addr, vid,
			    BATADV_NULL_IFINDEX, BATADV_NO_MARK);

	/* don't return reference to new softif_vlan */
	batadv_softif_vlan_put(vlan);

	return 0;
}