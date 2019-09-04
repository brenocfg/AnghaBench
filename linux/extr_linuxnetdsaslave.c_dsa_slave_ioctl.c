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
struct ifreq {int dummy; } ;
struct dsa_switch {TYPE_1__* ops; } ;
struct dsa_slave_priv {TYPE_2__* dp; } ;
struct TYPE_4__ {int index; int /*<<< orphan*/  pl; struct dsa_switch* ds; } ;
struct TYPE_3__ {int (* port_hwtstamp_get ) (struct dsa_switch*,int,struct ifreq*) ;int (* port_hwtstamp_set ) (struct dsa_switch*,int,struct ifreq*) ;} ;

/* Variables and functions */
#define  SIOCGHWTSTAMP 129 
#define  SIOCSHWTSTAMP 128 
 struct dsa_slave_priv* netdev_priv (struct net_device*) ; 
 int phylink_mii_ioctl (int /*<<< orphan*/ ,struct ifreq*,int) ; 
 int stub1 (struct dsa_switch*,int,struct ifreq*) ; 
 int stub2 (struct dsa_switch*,int,struct ifreq*) ; 

__attribute__((used)) static int dsa_slave_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct dsa_slave_priv *p = netdev_priv(dev);
	struct dsa_switch *ds = p->dp->ds;
	int port = p->dp->index;

	/* Pass through to switch driver if it supports timestamping */
	switch (cmd) {
	case SIOCGHWTSTAMP:
		if (ds->ops->port_hwtstamp_get)
			return ds->ops->port_hwtstamp_get(ds, port, ifr);
		break;
	case SIOCSHWTSTAMP:
		if (ds->ops->port_hwtstamp_set)
			return ds->ops->port_hwtstamp_set(ds, port, ifr);
		break;
	}

	return phylink_mii_ioctl(p->dp->pl, ifr, cmd);
}