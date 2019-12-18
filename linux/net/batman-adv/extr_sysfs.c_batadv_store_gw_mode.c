#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct kobject {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  mode; } ;
struct batadv_priv {TYPE_3__ gw; TYPE_2__* algo_ops; } ;
struct attribute {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  is_eligible; int /*<<< orphan*/  get_best_gw_node; } ;
struct TYPE_5__ {TYPE_1__ gw; } ;

/* Variables and functions */
#define  BATADV_GW_MODE_CLIENT 129 
 char* BATADV_GW_MODE_CLIENT_NAME ; 
 int BATADV_GW_MODE_OFF ; 
 char* BATADV_GW_MODE_OFF_NAME ; 
#define  BATADV_GW_MODE_SERVER 128 
 char* BATADV_GW_MODE_SERVER_NAME ; 
 size_t EINVAL ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  batadv_gw_check_client_stop (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_gw_reselect (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_gw_tvlv_container_update (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_info (struct net_device*,char*,char*,...) ; 
 struct net_device* batadv_kobj_to_netdev (struct kobject*) ; 
 int /*<<< orphan*/  batadv_netlink_notify_mesh (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_sysfs_deprecated (struct attribute*) ; 
 struct batadv_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t batadv_store_gw_mode(struct kobject *kobj,
				    struct attribute *attr, char *buff,
				    size_t count)
{
	struct net_device *net_dev = batadv_kobj_to_netdev(kobj);
	struct batadv_priv *bat_priv = netdev_priv(net_dev);
	char *curr_gw_mode_str;
	int gw_mode_tmp = -1;

	batadv_sysfs_deprecated(attr);

	/* toggling GW mode is allowed only if the routing algorithm in use
	 * provides the GW API
	 */
	if (!bat_priv->algo_ops->gw.get_best_gw_node ||
	    !bat_priv->algo_ops->gw.is_eligible)
		return -EINVAL;

	if (buff[count - 1] == '\n')
		buff[count - 1] = '\0';

	if (strncmp(buff, BATADV_GW_MODE_OFF_NAME,
		    strlen(BATADV_GW_MODE_OFF_NAME)) == 0)
		gw_mode_tmp = BATADV_GW_MODE_OFF;

	if (strncmp(buff, BATADV_GW_MODE_CLIENT_NAME,
		    strlen(BATADV_GW_MODE_CLIENT_NAME)) == 0)
		gw_mode_tmp = BATADV_GW_MODE_CLIENT;

	if (strncmp(buff, BATADV_GW_MODE_SERVER_NAME,
		    strlen(BATADV_GW_MODE_SERVER_NAME)) == 0)
		gw_mode_tmp = BATADV_GW_MODE_SERVER;

	if (gw_mode_tmp < 0) {
		batadv_info(net_dev,
			    "Invalid parameter for 'gw mode' setting received: %s\n",
			    buff);
		return -EINVAL;
	}

	if (atomic_read(&bat_priv->gw.mode) == gw_mode_tmp)
		return count;

	switch (atomic_read(&bat_priv->gw.mode)) {
	case BATADV_GW_MODE_CLIENT:
		curr_gw_mode_str = BATADV_GW_MODE_CLIENT_NAME;
		break;
	case BATADV_GW_MODE_SERVER:
		curr_gw_mode_str = BATADV_GW_MODE_SERVER_NAME;
		break;
	default:
		curr_gw_mode_str = BATADV_GW_MODE_OFF_NAME;
		break;
	}

	batadv_info(net_dev, "Changing gw mode from: %s to: %s\n",
		    curr_gw_mode_str, buff);

	/* Invoking batadv_gw_reselect() is not enough to really de-select the
	 * current GW. It will only instruct the gateway client code to perform
	 * a re-election the next time that this is needed.
	 *
	 * When gw client mode is being switched off the current GW must be
	 * de-selected explicitly otherwise no GW_ADD uevent is thrown on
	 * client mode re-activation. This is operation is performed in
	 * batadv_gw_check_client_stop().
	 */
	batadv_gw_reselect(bat_priv);
	/* always call batadv_gw_check_client_stop() before changing the gateway
	 * state
	 */
	batadv_gw_check_client_stop(bat_priv);
	atomic_set(&bat_priv->gw.mode, (unsigned int)gw_mode_tmp);
	batadv_gw_tvlv_container_update(bat_priv);

	batadv_netlink_notify_mesh(bat_priv);

	return count;
}