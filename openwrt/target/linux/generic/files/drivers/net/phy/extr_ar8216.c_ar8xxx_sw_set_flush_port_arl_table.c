#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct switch_val {int port_vlan; } ;
struct switch_dev {int ports; } ;
struct switch_attr {int dummy; } ;
struct ar8xxx_priv {int /*<<< orphan*/  reg_mutex; TYPE_1__* chip; } ;
struct TYPE_2__ {int (* atu_flush_port ) (struct ar8xxx_priv*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct ar8xxx_priv*,int) ; 
 struct ar8xxx_priv* swdev_to_ar8xxx (struct switch_dev*) ; 

int
ar8xxx_sw_set_flush_port_arl_table(struct switch_dev *dev,
				   const struct switch_attr *attr,
				   struct switch_val *val)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);
	int port, ret;

	port = val->port_vlan;
	if (port >= dev->ports)
		return -EINVAL;

	mutex_lock(&priv->reg_mutex);
	ret = priv->chip->atu_flush_port(priv, port);
	mutex_unlock(&priv->reg_mutex);

	return ret;
}