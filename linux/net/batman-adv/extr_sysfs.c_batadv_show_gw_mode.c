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
struct kobject {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  mode; } ;
struct batadv_priv {TYPE_3__ gw; TYPE_2__* algo_ops; } ;
struct attribute {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  is_eligible; int /*<<< orphan*/  get_best_gw_node; } ;
struct TYPE_5__ {TYPE_1__ gw; } ;

/* Variables and functions */
#define  BATADV_GW_MODE_CLIENT 129 
 char* BATADV_GW_MODE_CLIENT_NAME ; 
 char* BATADV_GW_MODE_OFF_NAME ; 
#define  BATADV_GW_MODE_SERVER 128 
 char* BATADV_GW_MODE_SERVER_NAME ; 
 int ENOENT ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct batadv_priv* batadv_kobj_to_batpriv (struct kobject*) ; 
 int /*<<< orphan*/  batadv_sysfs_deprecated (struct attribute*) ; 
 int sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t batadv_show_gw_mode(struct kobject *kobj, struct attribute *attr,
				   char *buff)
{
	struct batadv_priv *bat_priv = batadv_kobj_to_batpriv(kobj);
	int bytes_written;

	batadv_sysfs_deprecated(attr);

	/* GW mode is not available if the routing algorithm in use does not
	 * implement the GW API
	 */
	if (!bat_priv->algo_ops->gw.get_best_gw_node ||
	    !bat_priv->algo_ops->gw.is_eligible)
		return -ENOENT;

	switch (atomic_read(&bat_priv->gw.mode)) {
	case BATADV_GW_MODE_CLIENT:
		bytes_written = sprintf(buff, "%s\n",
					BATADV_GW_MODE_CLIENT_NAME);
		break;
	case BATADV_GW_MODE_SERVER:
		bytes_written = sprintf(buff, "%s\n",
					BATADV_GW_MODE_SERVER_NAME);
		break;
	default:
		bytes_written = sprintf(buff, "%s\n",
					BATADV_GW_MODE_OFF_NAME);
		break;
	}

	return bytes_written;
}