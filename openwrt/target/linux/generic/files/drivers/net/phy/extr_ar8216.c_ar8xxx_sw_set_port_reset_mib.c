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
struct switch_val {int port_vlan; } ;
struct switch_dev {int ports; } ;
struct switch_attr {int dummy; } ;
struct ar8xxx_priv {int /*<<< orphan*/  mib_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ar8xxx_has_mib_counters (struct ar8xxx_priv*) ; 
 int ar8xxx_mib_capture (struct ar8xxx_priv*) ; 
 int /*<<< orphan*/  ar8xxx_mib_fetch_port_stat (struct ar8xxx_priv*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ar8xxx_priv* swdev_to_ar8xxx (struct switch_dev*) ; 

int
ar8xxx_sw_set_port_reset_mib(struct switch_dev *dev,
			     const struct switch_attr *attr,
			     struct switch_val *val)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);
	int port;
	int ret;

	if (!ar8xxx_has_mib_counters(priv))
		return -EOPNOTSUPP;

	port = val->port_vlan;
	if (port >= dev->ports)
		return -EINVAL;

	mutex_lock(&priv->mib_lock);
	ret = ar8xxx_mib_capture(priv);
	if (ret)
		goto unlock;

	ar8xxx_mib_fetch_port_stat(priv, port, true);

	ret = 0;

unlock:
	mutex_unlock(&priv->mib_lock);
	return ret;
}