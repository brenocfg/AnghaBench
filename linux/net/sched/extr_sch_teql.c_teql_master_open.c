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
struct teql_master {TYPE_1__* dev; struct Qdisc* slaves; } ;
struct net_device {int mtu; scalar_t__ hard_header_len; unsigned int flags; } ;
struct Qdisc {int dummy; } ;
struct TYPE_2__ {int mtu; unsigned int flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int EUNATCH ; 
 unsigned int FMASK ; 
 unsigned int IFF_BROADCAST ; 
 unsigned int IFF_MULTICAST ; 
 unsigned int IFF_NOARP ; 
 unsigned int IFF_POINTOPOINT ; 
 scalar_t__ LL_MAX_HEADER ; 
 struct Qdisc* NEXT_SLAVE (struct Qdisc*) ; 
 struct teql_master* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (TYPE_1__*) ; 
 struct net_device* qdisc_dev (struct Qdisc*) ; 

__attribute__((used)) static int teql_master_open(struct net_device *dev)
{
	struct Qdisc *q;
	struct teql_master *m = netdev_priv(dev);
	int mtu = 0xFFFE;
	unsigned int flags = IFF_NOARP | IFF_MULTICAST;

	if (m->slaves == NULL)
		return -EUNATCH;

	flags = FMASK;

	q = m->slaves;
	do {
		struct net_device *slave = qdisc_dev(q);

		if (slave == NULL)
			return -EUNATCH;

		if (slave->mtu < mtu)
			mtu = slave->mtu;
		if (slave->hard_header_len > LL_MAX_HEADER)
			return -EINVAL;

		/* If all the slaves are BROADCAST, master is BROADCAST
		   If all the slaves are PtP, master is PtP
		   Otherwise, master is NBMA.
		 */
		if (!(slave->flags&IFF_POINTOPOINT))
			flags &= ~IFF_POINTOPOINT;
		if (!(slave->flags&IFF_BROADCAST))
			flags &= ~IFF_BROADCAST;
		if (!(slave->flags&IFF_MULTICAST))
			flags &= ~IFF_MULTICAST;
	} while ((q = NEXT_SLAVE(q)) != m->slaves);

	m->dev->mtu = mtu;
	m->dev->flags = (m->dev->flags&~FMASK) | flags;
	netif_start_queue(m->dev);
	return 0;
}