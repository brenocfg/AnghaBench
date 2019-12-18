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
struct net_device {int /*<<< orphan*/  tx_queue_len; int /*<<< orphan*/  ifindex; int /*<<< orphan*/  if_port; int /*<<< orphan*/  dma; int /*<<< orphan*/  irq; int /*<<< orphan*/  base_addr; int /*<<< orphan*/  mem_end; int /*<<< orphan*/  mem_start; int /*<<< orphan*/  type; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  mtu; } ;
struct net {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; int /*<<< orphan*/  dma; int /*<<< orphan*/  irq; int /*<<< orphan*/  base_addr; int /*<<< orphan*/  mem_end; int /*<<< orphan*/  mem_start; } ;
struct TYPE_3__ {int /*<<< orphan*/  sa_family; int /*<<< orphan*/  sa_data; } ;
struct ifreq {short ifr_flags; int /*<<< orphan*/  ifr_qlen; int /*<<< orphan*/  ifr_ifindex; TYPE_2__ ifr_map; TYPE_1__ ifr_hwaddr; int /*<<< orphan*/  ifr_mtu; int /*<<< orphan*/  ifr_metric; int /*<<< orphan*/  ifr_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOTTY ; 
#define  SIOCGIFFLAGS 135 
#define  SIOCGIFHWADDR 134 
#define  SIOCGIFINDEX 133 
#define  SIOCGIFMAP 132 
#define  SIOCGIFMETRIC 131 
#define  SIOCGIFMTU 130 
#define  SIOCGIFSLAVE 129 
#define  SIOCGIFTXQLEN 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct net_device* dev_get_by_name_rcu (struct net*,int /*<<< orphan*/ ) ; 
 scalar_t__ dev_get_flags (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,size_t) ; 

__attribute__((used)) static int dev_ifsioc_locked(struct net *net, struct ifreq *ifr, unsigned int cmd)
{
	int err;
	struct net_device *dev = dev_get_by_name_rcu(net, ifr->ifr_name);

	if (!dev)
		return -ENODEV;

	switch (cmd) {
	case SIOCGIFFLAGS:	/* Get interface flags */
		ifr->ifr_flags = (short) dev_get_flags(dev);
		return 0;

	case SIOCGIFMETRIC:	/* Get the metric on the interface
				   (currently unused) */
		ifr->ifr_metric = 0;
		return 0;

	case SIOCGIFMTU:	/* Get the MTU of a device */
		ifr->ifr_mtu = dev->mtu;
		return 0;

	case SIOCGIFHWADDR:
		if (!dev->addr_len)
			memset(ifr->ifr_hwaddr.sa_data, 0,
			       sizeof(ifr->ifr_hwaddr.sa_data));
		else
			memcpy(ifr->ifr_hwaddr.sa_data, dev->dev_addr,
			       min(sizeof(ifr->ifr_hwaddr.sa_data),
				   (size_t)dev->addr_len));
		ifr->ifr_hwaddr.sa_family = dev->type;
		return 0;

	case SIOCGIFSLAVE:
		err = -EINVAL;
		break;

	case SIOCGIFMAP:
		ifr->ifr_map.mem_start = dev->mem_start;
		ifr->ifr_map.mem_end   = dev->mem_end;
		ifr->ifr_map.base_addr = dev->base_addr;
		ifr->ifr_map.irq       = dev->irq;
		ifr->ifr_map.dma       = dev->dma;
		ifr->ifr_map.port      = dev->if_port;
		return 0;

	case SIOCGIFINDEX:
		ifr->ifr_ifindex = dev->ifindex;
		return 0;

	case SIOCGIFTXQLEN:
		ifr->ifr_qlen = dev->tx_queue_len;
		return 0;

	default:
		/* dev_ioctl() should ensure this case
		 * is never reached
		 */
		WARN_ON(1);
		err = -ENOTTY;
		break;

	}
	return err;
}