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
struct phy_device {struct ar8xxx_priv* priv; } ;
struct ar8xxx_priv {scalar_t__ use_count; int /*<<< orphan*/  dev; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ar8xxx_dev_list_lock ; 
 int /*<<< orphan*/  ar8xxx_free (struct ar8xxx_priv*) ; 
 int /*<<< orphan*/  ar8xxx_mib_stop (struct ar8xxx_priv*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_switch (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ar8xxx_phy_remove(struct phy_device *phydev)
{
	struct ar8xxx_priv *priv = phydev->priv;

	if (WARN_ON(!priv))
		return;

	phydev->priv = NULL;

	mutex_lock(&ar8xxx_dev_list_lock);

	if (--priv->use_count > 0) {
		mutex_unlock(&ar8xxx_dev_list_lock);
		return;
	}

	list_del(&priv->list);
	mutex_unlock(&ar8xxx_dev_list_lock);

	unregister_switch(&priv->dev);
	ar8xxx_mib_stop(priv);
	ar8xxx_free(priv);
}