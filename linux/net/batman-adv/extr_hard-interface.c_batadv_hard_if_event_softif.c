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
struct net_device {int dummy; } ;
struct batadv_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_NO_FLAGS ; 
#define  NETDEV_CHANGENAME 129 
#define  NETDEV_REGISTER 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  batadv_debugfs_rename_meshif (struct net_device*) ; 
 int /*<<< orphan*/  batadv_softif_create_vlan (struct batadv_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_sysfs_add_meshif (struct net_device*) ; 
 struct batadv_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int batadv_hard_if_event_softif(unsigned long event,
				       struct net_device *net_dev)
{
	struct batadv_priv *bat_priv;

	switch (event) {
	case NETDEV_REGISTER:
		batadv_sysfs_add_meshif(net_dev);
		bat_priv = netdev_priv(net_dev);
		batadv_softif_create_vlan(bat_priv, BATADV_NO_FLAGS);
		break;
	case NETDEV_CHANGENAME:
		batadv_debugfs_rename_meshif(net_dev);
		break;
	}

	return NOTIFY_DONE;
}