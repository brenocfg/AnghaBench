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
struct TYPE_4__ {int /*<<< orphan*/  sel_class; } ;
struct batadv_priv {TYPE_1__ gw; TYPE_3__* algo_ops; } ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* show_sel_class ) (struct batadv_priv*,char*) ;int /*<<< orphan*/  is_eligible; int /*<<< orphan*/  get_best_gw_node; } ;
struct TYPE_6__ {TYPE_2__ gw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct batadv_priv* batadv_kobj_to_batpriv (struct kobject*) ; 
 int /*<<< orphan*/  batadv_sysfs_deprecated (struct attribute*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct batadv_priv*,char*) ; 

__attribute__((used)) static ssize_t batadv_show_gw_sel_class(struct kobject *kobj,
					struct attribute *attr, char *buff)
{
	struct batadv_priv *bat_priv = batadv_kobj_to_batpriv(kobj);

	batadv_sysfs_deprecated(attr);

	/* GW selection class is not available if the routing algorithm in use
	 * does not implement the GW API
	 */
	if (!bat_priv->algo_ops->gw.get_best_gw_node ||
	    !bat_priv->algo_ops->gw.is_eligible)
		return -ENOENT;

	if (bat_priv->algo_ops->gw.show_sel_class)
		return bat_priv->algo_ops->gw.show_sel_class(bat_priv, buff);

	return sprintf(buff, "%i\n", atomic_read(&bat_priv->gw.sel_class));
}