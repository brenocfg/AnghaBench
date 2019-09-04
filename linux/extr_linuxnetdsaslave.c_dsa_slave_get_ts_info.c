#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct ethtool_ts_info {int dummy; } ;
struct dsa_switch {TYPE_1__* ops; } ;
struct dsa_slave_priv {TYPE_2__* dp; } ;
struct TYPE_4__ {int /*<<< orphan*/  index; struct dsa_switch* ds; } ;
struct TYPE_3__ {int (* get_ts_info ) (struct dsa_switch*,int /*<<< orphan*/ ,struct ethtool_ts_info*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct dsa_slave_priv* netdev_priv (struct net_device*) ; 
 int stub1 (struct dsa_switch*,int /*<<< orphan*/ ,struct ethtool_ts_info*) ; 

__attribute__((used)) static int dsa_slave_get_ts_info(struct net_device *dev,
				 struct ethtool_ts_info *ts)
{
	struct dsa_slave_priv *p = netdev_priv(dev);
	struct dsa_switch *ds = p->dp->ds;

	if (!ds->ops->get_ts_info)
		return -EOPNOTSUPP;

	return ds->ops->get_ts_info(ds, p->dp->index, ts);
}