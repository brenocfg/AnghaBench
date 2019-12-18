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
struct switch_dev {int dummy; } ;
struct adm6996_priv {int vlan_enabled; scalar_t__ model; int /*<<< orphan*/  reg_mutex; int /*<<< orphan*/  enable_vlan; } ;

/* Variables and functions */
 scalar_t__ ADM6996L ; 
 int /*<<< orphan*/  adm6996_apply_port_pvids (struct adm6996_priv*) ; 
 int /*<<< orphan*/  adm6996_apply_vlan_filters (struct adm6996_priv*) ; 
 int /*<<< orphan*/  adm6996_apply_vlan_filters_6996l (struct adm6996_priv*) ; 
 int /*<<< orphan*/  adm6996_disable_vlan (struct adm6996_priv*) ; 
 int /*<<< orphan*/  adm6996_disable_vlan_6996l (struct adm6996_priv*) ; 
 int /*<<< orphan*/  adm6996_enable_vlan (struct adm6996_priv*) ; 
 int /*<<< orphan*/  adm6996_enable_vlan_6996l (struct adm6996_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_devel (char*) ; 
 struct adm6996_priv* to_adm (struct switch_dev*) ; 

__attribute__((used)) static int
adm6996_hw_apply(struct switch_dev *dev)
{
	struct adm6996_priv *priv = to_adm(dev);

	pr_devel("hw_apply\n");

	mutex_lock(&priv->reg_mutex);

	if (!priv->enable_vlan) {
		if (priv->vlan_enabled) {
			if (priv->model == ADM6996L)
				adm6996_disable_vlan_6996l(priv);
			else
				adm6996_disable_vlan(priv);
			priv->vlan_enabled = 0;
		}
		goto out;
	}

	if (!priv->vlan_enabled) {
		if (priv->model == ADM6996L)
			adm6996_enable_vlan_6996l(priv);
		else
			adm6996_enable_vlan(priv);
		priv->vlan_enabled = 1;
	}

	adm6996_apply_port_pvids(priv);
	if (priv->model == ADM6996L)
		adm6996_apply_vlan_filters_6996l(priv);
	else
		adm6996_apply_vlan_filters(priv);

out:
	mutex_unlock(&priv->reg_mutex);

	return 0;
}